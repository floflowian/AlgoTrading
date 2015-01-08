%clear all
close all
symbol1='CHK';
symbol2='MUR';
[date1, high1, low1, open1, close1, vol1] = get_hist_stock_data(symbol1);
[date2, high2, low2, open2, close2, vol2] = get_hist_stock_data(symbol2);

date1=datestr(datenum(date1, 'yyyy-mm-dd'), 'yyyymmdd');
date2=datestr(datenum(date2, 'yyyy-mm-dd'), 'yyyymmdd');

date1=str2double(cellstr(date1));
date2=str2double(cellstr(date2)); % convert the date strings first into cell arrays and then into numeric format.

[date, idx1, idx2]=intersect(date1, date2); % find the intersection of the two data sets, and sort them in ascending order

close1= close1(idx1);
close2= close2(idx2);

trainingset=1:floor(length(date)/2);
testset = floor(length(date)/2)+1:length(date);

results= ols(close1(trainingset),close2(trainingset));
hedgeRatio = results.beta;

spread=close1-hedgeRatio*close2;

meanSpread=mean(spread(trainingset));

stdDevSpread=std(spread(trainingset));

figure(1)
plot(spread)
hold on
plot([trainingset testset],meanSpread,'yellow')
hold on
plot([trainingset testset],meanSpread+2*stdDevSpread,'black');
hold on
plot([trainingset testset],meanSpread-2*stdDevSpread,'black');
hold on
plot([trainingset testset],meanSpread+4*stdDevSpread,'red');
hold on
plot([trainingset testset],meanSpread-4*stdDevSpread,'red');
hold on
plot([trainingset testset],meanSpread+1*stdDevSpread,'green');
hold on
plot([trainingset testset],meanSpread-1*stdDevSpread,'green');
hold off
xlabel('t')
ylabel('Spread')
title('Spread vs Time')

zscore = (spread - meanSpread)./stdDevSpread;

longs=zscore<=-2; %buy when spread is more that 1 std dev away from mean

shorts=zscore>=2; %short when spread is more that 1 std dev away from mean

exits=(abs(zscore)<=1 | abs(zscore)>=4) ; %exit any position when spread comes within 0.5 std dev from mean

positions = NaN(length(date),2);

positions(longs, :) = repmat([1 -1], [length(find(longs)) 1]); % long entries
positions(shorts, :) = repmat([-1 1], [length(find(shorts)) 1]); % short entries
positions(exits,  :)=zeros(length(find(exits)), 2); % exit positions

positions=fillMissingData(positions);
positions(isnan(positions))=0;
cl=[close1 close2]; % combine the 2 price series

dailyret=(cl - lag1(cl))./lag1(cl);

pnl=sum(lag1(positions).*dailyret, 2);

cumulPnl=cumsum(pnl(testset));

figure(2)
plot(cumulPnl)
xlabel('t')
ylabel('Cumul PnL')
title('Cumul PnL vs Time')
sharpeTrainset=sqrt(252)*mean(pnl(trainingset(2:end)))./std(pnl(trainingset(2:end))) % the Sharpe ratio on the training set should be about 2.3

sharpeTestset=sqrt(252)*mean(pnl(testset))./std(pnl(testset)) % the Sharpe ratio on the test set should be about 1.5





