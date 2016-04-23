clear
close all
clc

load Feature.mat
%%Supervised Learning problem 

%Initialise normalised structures
trnFeat1 = cell(10,15);
tstFeat1 = cell(10,15);

%%not performed on Feature sets 2, as they are data type single and get
%%converted to doubles in the process which results in values of 
%%either 0 or 1
for x = 1 : 10
    for y = 1 : 15
        trnHist1 = hist(double(trnFeature_Set1{x,y})', 0:5:255)'./length(trnFeature_Set1{x,y});
        trnFeat1(x,y) = {trnHist1(:)'};
        
        tstHist1 = hist(double(tstFeature_Set1{x,y})', 0:5:255)'./length(tstFeature_Set1{x,y});
        tstFeat1(x,y) = {tstHist1(:)'};
    end
end

%%Create Labels
%%15 of each number 1 through 10.
Y = zeros(150,1);
for x = 0 : 9
    for y = 1 : 15
        Y((15*x)+y) = x+1;
    end
end

%%Collapse 2d array into 1d
%%Y(150) = feature sets for each image
X_trn = cell(150,1);
X_tst = cell(150,1);
for x = 0 : 9
    for y = 1 : 15        
        X_trn((15*x)+y) = trnFeat1(x+1, y);
        X_tst((15*x)+y) = tstFeat1(x+1, y);
    end
end

%%Turn 1d array of feature vectors into 2d array of samples/featurevectors
%%Y(150) = images/samples
%%X(6656) = feature vector
X_train = zeros(150, 6656);
X_test = zeros(150, 6656);
for x = 1 : 150
    for y = 1 : 6656 
        X_train(x,y) = X_trn{x,1}(1,y);
        X_test(x,y) = X_tst{x,1}(1,y);
    end
end

%% Option 1: Perform PCA
[coeff, score, latent] = pca(X_train, 'NumComponents',25);
[coeff2, score2, latent2] = pca(X_test, 'NumComponents', 25);

X_trainPCA = score;
X_testPCA = score2;

%% Option 2: Slice the feature vector into more manageable size(s)
X_trainSlice1 = X_train(:, 1:3328);
X_testSlice1 = X_test(:, 1:3328);
X_trainSlice2 = X_train(:, 3329:6656);
X_testSlice2 = X_test(:, 3329:6656);


%% Option 1-LDA Accuracy
LDAModel = fitcdiscr(X_trainPCA, Y); 
%%Testing Procedure
Y_tst_Predict = predict(LDAModel, X_testPCA);
%%Check accuracy
Diff = Y-Y_tst_Predict;
ind = find(Diff==0);
Right = numel(ind);
Wrong = numel(Y) - Right;
Accuracy = Right/(Right+Wrong);
disp('Performing PCA and then LDA.');
disp(['Accuracy on testing set is: ' num2str(Accuracy*100) '%']);
disp(' ');

confusionMatrix = confusionmat(Y, Y_tst_Predict);

%% Option 1-NN Accuracy
net = feedforwardnet([7,7,4]);
% Train NNs on the training dataset
net = train(net, X_trainPCA', Y');

% Testing Procedure
Y_tst_Predict = net(X_testPCA');
Y_tst_Predict = round(Y_tst_Predict);
% Check accuracy
Diff = Y-Y_tst_Predict';
ind = find(Diff==0);
Right = numel(ind);
Wrong = numel(Y) - Right;
Accuracy = Right/(Right+Wrong);
disp('Performing PCA and then NN.');
disp(['Accuracy on testing set is: ' num2str(Accuracy*100) '%']);
disp(' ');


%% Option 2.A-LDA Accuracy
LDAModel = fitcdiscr(X_trainSlice1, Y); 
%%Testing Procedure
Y_tst_Predict = predict(LDAModel, X_testSlice1);
%%Check accuracy
Diff = Y-Y_tst_Predict;
ind = find(Diff==0);
Right = numel(ind);
Wrong = numel(Y) - Right;
Accuracy = Right/(Right+Wrong);
disp('Slicing test and training data in half (first half) and then performing LDA.');
disp(['Accuracy on testing set is: ' num2str(Accuracy*100) '%']);
disp(' ');


%% Option 2.B-LDA Accuracy -- note: contains a zero within-class variance, so need to change the discrim type

%%psudeoLinear = 52.6667%  (All classes have the same covariance matrix.
%%The software inverts the covariance matrix using the pseudo
%%inverse)[ref:http://uk.mathworks.com/help/stats/fitcdiscr.html]

LDAModel = fitcdiscr(X_trainSlice2, Y, 'discrimType', 'pseudoLinear'); 
%%Testing Procedure
Y_tst_Predict = predict(LDAModel, X_testSlice2);
%%Check accuracy
Diff = Y-Y_tst_Predict;
ind = find(Diff==0);
Right = numel(ind);
Wrong = numel(Y) - Right;
Accuracy = Right/(Right+Wrong);
disp('Slicing test and training data in half (second half) and then performing LDA.');
disp(['Accuracy on testing set is: ' num2str(Accuracy*100) '%']);


clear x y Wrong LDAModel Diff ind Accuracy Right