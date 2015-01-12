function [ correlation, cointegration ] = getCorCoinPair( symbol1, symbol2 )

[date1, high1, low1, open1, close1, vol1] = get_hist_stock_data(symbol1);
[date2, high2, low2, open2, close2, vol2] = get_hist_stock_data(symbol2);

date1=datestr(datenum(date1, 'yyyy-mm-dd'), 'yyyymmdd');
date2=datestr(datenum(date2, 'yyyy-mm-dd'), 'yyyymmdd');

date1=str2double(cellstr(date1));
date2=str2double(cellstr(date2)); % convert the date strings first into cell arrays and then into numeric format.

%close1=close1(length(close1)-500:end); %Lookback period of 100days
%date1=date1(length(date1)-500:end); 

[date, idx1, idx2]=intersect(date1, date2); % find the intersection of the two data sets, and sort them in ascending order

close1= close1(idx1);
close2= close2(idx2);

trainingset=1:floor(length(date)/2);
testset = floor(length(date)/2)+1:length(date);

res=cadf(close1(trainingset), close2(trainingset), 0, 1);
cointegration = res.adf;

correlation=corr(close1(trainingset),close2(trainingset));


end

