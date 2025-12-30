function likelihood = calculateLikelihood(observed, mean, sigma)
  
  norm = 1 ./ (sqrt(2*pi.*sigma.^2));
  exponent = -0.5 * (observed - mean).^2 ./ sigma.^2;

  likelihood = norm .* exp(exponent);
endfunction