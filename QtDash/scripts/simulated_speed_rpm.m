function [time, obs_speed obs_rpm obs_ratio true_gear] = simulated_speed_rpm()
  % ---------------------------------------------------------
  % Vehicle Constants
  % ---------------------------------------------------------
  gear_ratios = [4.03, 2.16, 1.37, 1.00, 0.82];
  rear_end_ratio = 3.31;
  tire_diameter_in = 24.9;

  % Conversion Factors
  tire_circumference_ft = (tire_diameter_in * pi) / 12;
  tire_revs_per_mile = 5280 / tire_circumference_ft;

  % Calculate "RPM per MPH" for every gear
  % RPM = MPH * Ratio * FinalDrive * (RevsPerMile / 60)
  k_const = rear_end_ratio * (tire_revs_per_mile / 60);
  ratios_rpm_per_mph = gear_ratios .* k_const;

  % ---------------------------------------------------------
  % Simulation Setup
  % ---------------------------------------------------------
  dt = 50e-3; % 50ms sample time
  T = 60;     % 40 seconds duration
  num_samples = floor(T/dt);
  time = linspace(0, T, num_samples);

  % Noise Parameters
  speed_noise_std = 1.5;  % MPH noise
  rpm_noise_std = 40.0;   % RPM noise

  % Driver/Car Logic Parameters
  idle_rpm = 850;
  shift_point_rpm = 3500; % Driver shifts when RPM hits this
  accel_rate = 3.5;       % MPH per second
  brake_rate = 8.0;       % MPH per second decel
  max_speed = 65;

  % Initialize Arrays
  true_speed_mph = zeros(1, num_samples);
  true_rpm = zeros(1, num_samples);
  true_gear = zeros(1, num_samples); % 0 = Neutral
  clutch_is_pressed = false;

  % Initial State
  current_speed = 0;
  current_gear_idx = 1; % Start in 1st gear (waiting)
  state = 'IDLE'; % States: IDLE, ACCEL, CRUISE, BRAKE

  % ---------------------------------------------------------
  % Simulation Loop
  % ---------------------------------------------------------
  for k = 1:num_samples
      t = time(k);

      % --- State Machine ---
      if t < 2
          state = 'IDLE';
      elseif current_speed < max_speed && strcmp(state, 'BRAKE') == 0
          state = 'ACCEL';
      elseif t > 25
          state = 'BRAKE';
          clutch_is_pressed = true; % Clutch in for braking
      else
          state = 'CRUISE';
      end

      % --- Physics & Driver Input ---

      switch state
          case 'IDLE'
              current_speed = 0;
              current_rpm = idle_rpm;
              true_gear(k) = 0; % Neutral

          case 'ACCEL'
              current_speed = current_speed + (accel_rate * dt);

              % Calculate RPM for current gear
              current_ratio = ratios_rpm_per_mph(current_gear_idx);
              current_rpm = current_speed * current_ratio;

              % Shift Logic: If RPM is too high, shift up
              if current_rpm > shift_point_rpm && current_gear_idx < 5
                  current_gear_idx = current_gear_idx + 1;
                  % Recalculate RPM for new gear (Instant shift for simplicity)
                  current_ratio = ratios_rpm_per_mph(current_gear_idx);
                  current_rpm = current_speed * current_ratio;
              end

              % Physical limit: Don't drop below idle if moving
              current_rpm = max(current_rpm, idle_rpm);
              true_gear(k) = current_gear_idx;

          case 'CRUISE'
              current_speed = max_speed;
              current_ratio = ratios_rpm_per_mph(current_gear_idx);
              current_rpm = current_speed * current_ratio;
              true_gear(k) = current_gear_idx;

          case 'BRAKE'
              % Decelerate
              current_speed = current_speed - (brake_rate * dt);
              if current_speed < 0
                  current_speed = 0;
              end

              % Clutch is in: Engine drops to idle
              % (Add a little wobble to idle to make it realistic)
              current_rpm = idle_rpm + 50*sin(t*5);

              true_gear(k) = 0; % Technically gear might be selected, but clutch is in
      end

      % Store Ground Truth
      true_speed_mph(k) = current_speed;
      true_rpm(k) = current_rpm;
  end

  % ---------------------------------------------------------
  % Generate Observations (Add Noise)
  % ---------------------------------------------------------
  obs_speed = true_speed_mph + randn(1, num_samples) * speed_noise_std;
  obs_rpm = true_rpm + randn(1, num_samples) * rpm_noise_std;

  % Handle negative noise spikes (Physics constraint)
  obs_speed(obs_speed < 0) = 0;
  obs_rpm(obs_rpm < 0) = 0;

  % ---------------------------------------------------------
  % Visualization
  % ---------------------------------------------------------
  figure(1); clf;

  subplot(3,1,1);
  plot(time, obs_speed, 'b', 'LineWidth', 1); hold on;
  plot(time, true_speed_mph, 'c--', 'LineWidth', 2);
  ylabel('Speed (MPH)');
  legend('Observed', 'True');
  title('Simulation Data: 1-5 Shift & Braking');
  grid on;
  hold off;

  subplot(3,1,2);
  plot(time, obs_rpm, 'r', 'LineWidth', 1); hold on;
  plot(time, true_rpm, 'm--', 'LineWidth', 2);
  ylabel('Engine RPM');
  grid on;
  hold off;

  subplot(3,1,3);
  % Calculate Observed Ratio for visualization
  % Avoid divide by zero
  safe_speed = obs_speed;
  safe_speed(safe_speed < 2) = nan;
  obs_ratio = obs_rpm ./ safe_speed;

  plot(time, obs_ratio, 'k.', 'MarkerSize', 5); hold on;
  ylabel('Ratio (RPM/MPH)');
  xlabel('Time (s)');
  ylim([0, 200]);
  title('Observed Ratio (RPM / MPH)');
  grid on;
  hold off;

  % Draw expected gear lines
##  colors = ['g', 'b', 'm', 'c', 'r'];
##  for i = 1:5
##      yline(ratios_rpm_per_mph(i), ['--', colors(i)], ['Gear ' num2str(i)]);
##  end

endfunction
