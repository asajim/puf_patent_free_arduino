function [plus, percentage] = correlation_between_bits(data)
% SCRIPT TO CALCULATE PROBABILITY NEXT n BITS IS AFFECTED BY A VALUE

% get parameter 
d = data(1,1);
sz = size(d{:});
row_count = sz(1);
col_count = sz(2);
n_bit_to_compare = 128;
% calculate the probability
plus = zeros(1,n_bit_to_compare);
minus = zeros(1,n_bit_to_compare);
sum = zeros(1,n_bit_to_compare);
total = 0;
rxx = 0;
for a = 1:1
    dt = data(1,a);
    b = dt{:};
    for i=1:row_count-(floor(n_bit_to_compare/col_count))
       for j=1:col_count
           w = b(i,j);
           if (w == 1)
               total = total + 1;
               for k=1:n_bit_to_compare
                    jk = j+k;
                    p = floor(jk/col_count);
                    q = mod(jk,col_count) ;
                    if (q == 0)
                        q = 32;
                    end
                    if (i+p>row_count)
                        continue
                    end
                    v = b(i+p, q);
%                     total = total + 1;
                    if (v == 1)
                       rxx = rxx + 1;
                       plus(1,k) = plus(1,k) + 1;
                       sum(1,k) = sum(1,k) + 1;
                    else
                       rxx = rxx - 1;
                       minus(1,k) = minus(1,k) + 1;
                       sum(1,k) = sum(1,k) - 1;
                   end
               end
           end
       end
    end
end
% total
% plus
percentage = plus/total;
end
