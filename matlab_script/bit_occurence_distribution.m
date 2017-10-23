function [percentage, count_data] = bit_occurence_distribution(data)
% CALCULATING THE STABLE BIT 0 OR 1
d = data(1,1);
sz = size(d{:});
row_count = sz(1);
col_count = sz(2);

% sum all data
sum_data = zeros(row_count,col_count);
% c = data(1,1)
for i=1:size(data,2);
    a = data(1,i);
    arr = a{:};
    sum_data = sum_data + arr;
end
% sum_data

values = unique(sum_data);
count_data = [values,histc(sum_data(:),values)];
values
count_data

length = row_count*col_count;
percentage = [];
for i=1:size(values)
    a = (count_data(i,2)/length)*100;
    percentage = [percentage; count_data(i,1) a];
end


end
