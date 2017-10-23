function [differences, sum_differences, percentage_sum_differences] = hamming_distance(data)
% Hamming_distance calculate hamming distance between all elements in data

% differences per bit
differences = {};
% total difference
sum_differences = {};
% percentage total difference
percentage_sum_differences = {};
for i=1:size(data,2)
    a = data(1,i);
    aa = a{:};
    % number of element    
    num_el = numel(aa);
    for j=i+1:size(data,2)
        b = data(1,j);
        bb = b{:};
        diff_str = strcat(num2str(i),"-",num2str(j));
        difference = abs(aa-bb);
        differences = [differences; [difference]];
        sum_difference = sum(sum(difference));
        sum_differences = [sum_differences; diff_str sum_difference];
        percentage = sum_difference/num_el*100;
        percentage_sum_differences = [percentage_sum_differences; diff_str   percentage];
    end
end
end

