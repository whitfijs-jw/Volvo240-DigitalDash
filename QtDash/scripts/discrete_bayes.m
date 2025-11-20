clear; clc;

gear_ratios= [4.03, 2.16, 1.37, 1.00, 0.82];
rear_end_ratio=3.31
ratio_delta=0.25
speed_drop_out=5
speed_drop_out_units="mph"
idle_high_rpm=1000
idle_low_rpm=500
tire_diameter_miles = 0.0003929924
tire_diameter_in = 24.9;

Tg = (60 * (tire_diameter_miles * pi) ./ (gear_ratios .* rear_end_ratio)) .^ -1

[time, observed_speed_mph observed_rpm observed_ratio true_gear] = simulated_speed_rpm();

sigma_noise = 4.0; # single sigma
probs = [0.9, 0.02, 0.02, 0.02, 0.02, 0.02];
sigma_noise = Tg * 0.03 # sigma per gear

N = 4;
filter_kernel = ones(1,N) ./ N;

for ii = 1:length(observed_speed_mph)
  if ii >= 2
    probs(ii,:) = probs(ii-1,:);
  endif

  if (ii > length(filter_kernel))
    filtered_speed_mph(ii) = sum(observed_speed_mph(ii-(N-1):ii) .* filter_kernel);
    filtered_rpm(ii) = sum(observed_rpm(ii-(N-1):ii) .* filter_kernel);
  else
    filtered_speed_mph(ii) = observed_speed_mph(ii);
    filtered_rpm(ii) = observed_rpm(ii);
  endif

  if (filtered_speed_mph(ii) < speed_drop_out) || (filtered_rpm(ii) < idle_high_rpm)
    probs(ii,:) = [1.0, 0.0, 0.0, 0.0, 0.0, 0.0];
  endif

  if filtered_speed_mph(ii) != 0
    T_observed(ii) = filtered_rpm(ii) / filtered_speed_mph(ii);
  else
    probs(ii,:) = [1.0, 0.0, 0.0, 0.0, 0.0, 0.0];
    T_observed(ii) = 0.0;
  endif

  if ii >=2
    ratio_delta = abs(T_observed(ii)-T_observed(ii-1));
  else
    ratio_delta = 0.0;
  endif

  stability_threshold = 5.0;
  stability_penalty = 1.0; #exp(-(ratio_delta.^2) / stability_threshold)

  norm = 1 ./ (sqrt(2*pi.*sigma_noise.^2));
  exponent = -0.5 * (T_observed(ii) - Tg).^2 ./ sigma_noise.^2;

  likelihood(ii,1) = 1e-6;
  likelihood(ii,2:6) = norm .* exp(exponent);
  likelihood(ii,2:6) = likelihood(ii,2:6) .* stability_penalty;

  posterior = likelihood(ii,:) .* probs(ii,:);

  if sum(posterior) == 0
    probs(ii,:) = [1.0, 0.0, 0.0, 0.0, 0.0, 0.0];
  else
    probs(ii,:) = posterior / sum(posterior);
  endif

  estimated_gear(ii) = find(probs(ii,:) == max(probs(ii,:)));
  confidence(ii) = probs(ii, estimated_gear(ii));

  noise_floor = 0.1;
  probs(ii,:) = probs(ii,:) + noise_floor;
  probs(ii,:) = probs(ii,:) / sum(probs(ii,:));

  if ii >= 2
    if estimated_gear(ii) == estimated_gear(ii-1)
      con_count = 0;
    else
      con_count++;
      if con_count <= 5
        estimated_gear(ii) = estimated_gear(ii-1);
      else
        con_count = 0;
      endif
    endif
  endif
endfor

subplot(3,1,1)
plot(time, [observed_speed_mph; filtered_speed_mph], "Linewidth", [2.0])
ylabel 'Speed (mph)'
xlabel 'time (sec)'
legend 'observed speed' 'filtered speed'
grid on;

subplot(3,1,2)
plot(time, [observed_rpm; filtered_rpm], "Linewidth", [2.0])
ylabel 'RPM'
xlabel 'time (sec)'
legend 'observed RPM' 'filtered RPM'
grid on;

subplot(3,1,3)
all_gears = [0.0,4.03, 2.16, 1.37, 1.00, 0.82];
plot(time, [all_gears(estimated_gear); all_gears(true_gear+1); confidence], "Linewidth", [2.0])
ylabel 'gear ratio + confidence'
xlabel 'time (sec)'
legend 'Estimated Gear Ratio' 'True Gear Ratio' 'Confidence'
grid on;
