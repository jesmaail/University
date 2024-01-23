clear
close all
clc

[X,Y] = wine_dataset;
X = X';
[~,Y] = find(Y');
FeatureSpace = 1:13; % Use all features
% Divide the dataset into a training and testing class
idx = crossvalind('Kfold',Y,2);
X_trn = X(idx==1,FeatureSpace);
Y_trn = Y(idx==1,:);
X_tst = X(idx==2,FeatureSpace);
Y_tst = Y(idx==2,:);



%%%Training - create a feedforward NN using 1 layer with 7 hidden nodes
net = feedforwardnet(7);
% Train NNs on the training dataset
net = train(net,X_trn',Y_trn');
% Visualise the structure of NNs
view(net);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%Testing Procedure - feed test observations into the NN
Y_tst_Predict = net(X_tst');
% Why do we do this? Try checking Y_tst_Predict before running this line
Y_tst_Predict = round(Y_tst_Predict)';

% Check accuracy
nCorrectPredictions = sum(Y_tst==Y_tst_Predict);
Accuracy = nCorrectPredictions/length(Y_tst);
fprintf('Accuracy on testing set is: %.4f%%\n',Accuracy*100);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%