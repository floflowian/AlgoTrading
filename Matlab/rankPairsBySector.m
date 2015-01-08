clear all;
close all;
[num, txt]=xlsread('Data/Energy.xlsx');
symbols=txt(2:end,1);

[idx2, idx1] = find(true(numel(symbols),numel(symbols)));
pairs = [reshape(symbols(idx1), [], 1), reshape(symbols(idx2), [], 1)];

idRemove=[];
for i=0:floor(size(symbols,1))
    idRemove=[idRemove size(symbols,1)*i+1:size(symbols,1)*i+1+i];
end
idRemove(idRemove>size(pairs,1))=[];
pairs(idRemove,:)=[];

vectorCorr=zeros(size(pairs,1),1);
vectorCoin=zeros(size(pairs,1),1);
for i=1:size(pairs,1)
    i
    [correlation,cointegration]=testPair(char(pairs(i,1)),char(pairs(i,2)));
    vectorCorr(i)= correlation;
    vectorCoin(i)= cointegration;
end

minimumCorr=0.90;
maximumCoin=-3.34;

selectedByCorr=find(vectorCorr>minimumCorr);
selectedByCoin=find(vectorCoin<maximumCoin);
selectedByBoth=intersect(selectedByCorr,selectedByCoin);
selectedPairs=pairs(selectedByBoth,:);