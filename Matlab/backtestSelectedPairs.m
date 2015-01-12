%clear all;
%close all;

selectedPairs = rankPairsBySector('Staples');

nbPairs=size(selectedPairs,1);

entryLong=2; %buy when spread is more that -2 std dev away from mean
entryShort=2; %short when spread is more that 2 std dev away from mean
exitOrder=1; %exit position when spread is back in the 1*std range
stoploss=4; %Trigger stoploss of spread distance w/ mean exceeds 4*std

for i=1:nbPairs    
    disp(strcat('Backtest ',num2str(i),'/',num2str(nbPairs)))
   [ cumulPnl,sharpeTrainset,sharpeTestset,spread ,trainingset,testset ] = backtestPair( char(selectedPairs(i,1)), char(selectedPairs(i,2)), entryLong, entryShort, exitOrder,stoploss,0 );
   if(i==1)
       cumulPnl_all=zeros(nbPairs,length(cumulPnl));
       spread_all=zeros(nbPairs,length(spread));
       sharpeTrainset_all=zeros(nbPairs,1);
       sharpeTestset_all=zeros(nbPairs,1);
   end
   cumulPnl_all(i,1:size(cumulPnl,1))=cumulPnl;
   spread_all(i,1:size(spread,1))=spread;
   sharpeTrainset_all(i)=sharpeTrainset;
   sharpeTestset_all(i)=sharpeTestset;
end

monitorIndex = 74;

meanSpread=mean(spread_all(monitorIndex,trainingset));

stdDevSpread=std(spread_all(monitorIndex,trainingset));

figure(1)
plot(spread_all(monitorIndex,:))
hold on
plot([trainingset testset],meanSpread,'yellow')
hold on
plot([trainingset testset],meanSpread+entryShort*stdDevSpread,'black');
hold on
plot([trainingset testset],meanSpread-entryLong*stdDevSpread,'black');
hold on
plot([trainingset testset],meanSpread+stoploss*stdDevSpread,'red');
hold on
plot([trainingset testset],meanSpread-stoploss*stdDevSpread,'red');
hold on
plot([trainingset testset],meanSpread+exitOrder*stdDevSpread,'green');
hold on
plot([trainingset testset],meanSpread-exitOrder*stdDevSpread,'green');
hold off
xlabel('t')
ylabel('Spread')
title('Spread vs Time')


figure(2)
plot(cumulPnl_all(monitorIndex,:))
xlabel('t')
ylabel('Cumul PnL')
title('Cumul PnL vs Time')