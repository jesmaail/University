clear
close all
clc

%%%Load the Data%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
load fisheriris;
X = meas;
Y = zeros(size(species));
for i = 1:numel(species)
    if strcmp(species(i),'setosa') == 1
        Y(i) = 1;
    elseif strcmp(species(i),'versicolor') == 1
        Y(i) = 2;
    elseif strcmp(species(i),'virginica') == 1
        Y(i) = 3;
    end
end

FeatureSpace = [3,4];

% Divide the dataset into a training and testing class
idx = crossvalind('Kfold',Y,2);
X_trn = X(idx==1,FeatureSpace);
Y_trn = Y(idx==1,:);
X_tst = X(idx==2,FeatureSpace);
Y_tst = Y(idx==2,:);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%Construct a multi-class classifier by fitting a set of binary svm
%%%classifiers using one v.s all scheme.%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Create an SVM template, and specify the Gaussian kernel.
% It is good practice to standardize the predictors.
tempSVM = templateSVM('Standardize',true,'KernelFunction','gaussian');
% Fit a multi-class SVM classifier
Mdl = fitcecoc(X_trn,Y_trn,'Learners',tempSVM,'FitPosterior',true,'Verbose',2);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



%%%Pass the test observations to multi-class SVM 'Mdl'%%%%%%%%%%%%%%%%%%%%%
Y_tst_Predict = predict(Mdl,X_tst);

% Check accuracy
nCorrectPredictions = sum(Y_tst==Y_tst_Predict);
Accuracy = nCorrectPredictions/length(Y_tst);
fprintf('Accuracy on testing set is: %.4f%%\n',Accuracy*100);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
