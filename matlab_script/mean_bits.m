function [means, mean_all] = mean_bits(data)
% mean_bits CALCULATE MEAN BITS

% means of all bits
means = {};
mean_all = 0;
for i=1:size(data,2)
    a = data(1,i);
    aa = a{:};
    % number of element    
    num_el = numel(aa);
    sum_bit = sum(sum(aa));
    mean = sum_bit / num_el;
    mean_all = mean_all + mean;
    means = [means; strcat(num2str(i),"") mean];
end
mean_all = mean_all/size(data,2);
end