function [distance] = inter_distance(folderA, folderB)
% SCRIPT TO CALCULATE HAMMING DISTANCE
% clear all
% %% load data
data1 = {};
data2 = {};
% files = dir('*.c');
% files1 = dir(fullfile('/Users/ades17/Documents/Thesis/Software/matlab/131017/', '*.c'));
% files2 = dir(fullfile('/Users/ades17/Documents/Thesis/Software/matlab/171017C/', '*.c'));
files1 = dir(fullfile(folderA, '*.c'));
files2 = dir(fullfile(folderB, '*.c'));
% n_data = size(files1,1);
for i=1:10
    data1 = [data1, importdata(fullfile(files1(i).folder, files1(i).name))];
    data2 = [data2, importdata(fullfile(files2(i).folder, files2(i).name))];
end

% differences per bit
differences = {};
% total difference
sum_differences = {};
% percentage total difference
percentage_sum_differences = {};
for i=1:size(data1,2)
    a = data1(1,i);
    aa = a{:};
    % number of element    
    num_el = numel(aa);
    for j=1:size(data2,2)
        b = data2(1,j);
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

differences
distance = mean(mean(str2double(percentage_sum_differences(:,2))));
end