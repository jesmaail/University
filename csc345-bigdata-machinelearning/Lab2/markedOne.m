clear
close all
clc
load markedTaskOne.mat

X = 0.1:0.1:1;

mdl = fitlm(X,Y_Observation,'linear');
h3 = figure;
hold on;
plotAdded(mdl);
% plot true function in green
%plot(-0.2:0.1:1.2, 1.2+3.25*(-0.2:0.1:1.2), '-g', 'LineWidth', 1);
hold off;
disp(['-->Model: w0 = ' num2str(mdl.Coefficients{1,1}) ' w1= ' num2str(mdl.Coefficients{2,1}) ' MSError = ' num2str(mdl.MSE)]);

