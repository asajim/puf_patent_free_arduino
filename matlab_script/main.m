clear all
%% load data
data = {};
% files = dir('*.c');
% files = dir(fullfile('/Users/ades17/Documents/Thesis/Software/matlab/23K256/191017A/', '*.c'));
files = dir(fullfile('/Users/ades17/Documents/Thesis/Software/matlab/23LC1024/131017/', '*.c'));
n_data = size(files,1);
for i=1:10
    data = [data, importdata(fullfile(files(i).folder, files(i).name))];
end
%% CALCULATE DIFFERENCE / HAMMING DISTANCE
[differences, sum_differences, percentage_sum_differences] = hamming_distance(data);
a = percentage_sum_differences(:,2);
a
mean(str2double(a))
%% CALCULATE MEAN OF ALL BITS
% [means, mean_all] = mean_bits(data);
% means(:,2)
% mean_all
%% CALCULATING THE STABLE BIT 0 OR 1
% [percentage, count_data] = bit_occurence_distribution(data);
% create plot
% figure('name','Distribution of bit (Left most(0) -> stable 0, Right most(10) -> stable 1)');
% subplot(2,1,1)
% percentage
% count_data
% bar(percentage(:,1), percentage(:,2))
% ylim([0 100])
% title('Shown in percentage')
% subplot(2,1,2)
% area(count_data(:,1), count_data(:,2))
% title('Shown in total count')
%% CALCULATE PROBABILITY NEXT n BITS IS AFFECTED BY A VALUE
% [plus, percentage] = correlation_between_bits(data);
% figure
% % subplot(3,1,1)
% % plot(plus)
% % subplot(3,1,2)
% % plot(sum)
% % subplot(3,1,3)
% % plot(minus)
% plot(percentage)
% xlabel('Offset')
% ylabel('Probability bit q+x=1 given bit q=1')
% xlim([1 128])
% % ylim([0.5 0.8])
% % rxx
%% DEBIASING
% new_data = {};
% for i=1:size(data,2)
%     [result, count_data] = debiasing(data(1,i));
%     count_data
%     new_data = [new_data, result];
% end
% % new_data
% % hamming_distance(new_data)
% m = new_data(1,1);
% m1 = m{:};
% m2 = m1(1:100000);
% for i=2:size(new_data,2)
%     n = new_data(1,i);
%     n1 = n{:};
%     n2 = n1(1:100000);
%     k = abs(m2-n2);
%     sum(k)
% end