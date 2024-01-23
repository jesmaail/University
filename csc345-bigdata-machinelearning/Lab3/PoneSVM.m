clear
close all
clc

%%%Load the Data%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
[X,Y] = wine_dataset;
X = X';
[~,Y] = find(Y');
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



%%%Visualisation%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%DO NOT NEED TO FULLY UNDERSTAND THIS PART, IT IS ONLY VISUALISATION%%
% Showing the posterior probability of the trained model over training set
[label,~,~,Posterior] = resubPredict(Mdl,'Verbose',1);
table(Y_trn(),label(),Posterior(),'VariableNames',{'TrueLabel','PredLabel','Posterior'})
% Start by visualising the splitting boundary
% It is very slow on the machine without OpenGL support, you can comments
% this section out if you like to speed up.
xMax = max(X_trn);
xMin = min(X_trn);
x1Pts = linspace(xMin(1),xMax(1));
x2Pts = linspace(xMin(2),xMax(2));
[x1Grid,x2Grid] = meshgrid(x1Pts,x2Pts);
[~,~,~,PosteriorRegion] = predict(Mdl,[x1Grid(:),x2Grid(:)]);
figure;
contourf(x1Grid,x2Grid,reshape(max(PosteriorRegion,[],2),size(x1Grid,1),size(x1Grid,2)));
h = colorbar;
h.YLabel.String = 'Maximum posterior';
h.YLabel.FontSize = 15;
hold on
gh = gscatter(X_trn(:,1),X_trn(:,2),Y_trn,'kgk','*xd',8);
gh(2).LineWidth = 2;
gh(3).LineWidth = 2;
gh2 = gscatter(X_tst(:,1),X_tst(:,2),Y_tst,'krk','*xd',8);
gh2(2).LineWidth = 0.5;
gh2(3).LineWidth = 0.5;
title 'Wine Measurements and Maximum Posterior';
xlabel 'Feature One';
ylabel 'Feature Two';
axis tight
legend(gh,'Location','NorthWest')
legend(gh2,'Location','NorthWest')
hold off
% End visualisation of the splitting boundary
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
