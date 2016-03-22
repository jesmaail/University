clear
close all
clc

load Feature.mat

%Supervised Learning problem 
%Plan:
%%Perform LDA to reduce Dimensionality
%%Perform K-means to cluster the data

%Initialise normalised structures
trnFeat1 = cell(10,15);
tstFeat1 = cell(10,15);

%trnFeat2 = cell(10,15);
%tstFeat2 = cell(10,15);

for x = 1 : 10
    for y = 1 : 15
        trnHist1 = hist(double(trnFeature_Set1{x,y})', 0:5:255)'./length(trnFeature_Set1{x,y});
        trnFeat1(x,y) = {trnHist1(:)'};
        
        tstHist1 = hist(double(tstFeature_Set1{x,y})', 0:5:255)'./length(tstFeature_Set1{x,y});
        tstFeat1(x,y) = {tstHist1(:)'};
        
        
        %trnHist2 = hist(trnFeature_Set2{x,y}', 0:5:255)'./length(trnFeature_Set2{x,y});
        %trnFeat2(x,y) = {trnHist2(:)'};   
        
        %tstHist2 = hist(tstFeature_Set2{x,y}', 0:5:255)'./length(tstFeature_Set2{x,y});
        %tstFeat2(x,y) = {tstHist2(:)'};
    end
end

%Features = {'tick'; 'trilobite'; 'umbrella'; 'watch'; 'water lily'; 'wheelchair'; 'wild cat'; 'windsor chair'; 'wrench'; 'yin yang'};

%Create Labels
Y = zeros(150,1);
for x = 0 : 9
    for y = 1 : 15
        Y((15*x)+y) = x+1;
    end
end


X_trn = cell(150,1);
X_tst = cell(150,1);
for x = 0 : 9
    for y = 1 : 15        
        X_trn((15*x)+y) = trnFeat1(x+1, y);
        X_tst((15*x)+y) = tstFeat1(x+1, y);
    end
end

% 1=6656  2=468
X_train = zeros(150, 6656);
X_test = zeros(150, 6656);
for x = 1 : 150
    for y = 1 : 6656 
        X_train(x,y) = X_trn{x,1}(1,y);
        X_test(x,y) = X_tst{x,1}(1,y);
    end
end

X_train = X_train(:, 1:4000);
X_test = X_test(:, 1:4000);

[coeff,score,latent] = pca(X_train);

LDAModel = fitcdiscr(X_train, Y); 
%idx = predict(LDAModel, X_test);

% Testing Procedure
Y_tst_Predict = predict(LDAModel, X_test);
% Check accuracy
Diff = Y-Y_tst_Predict;
ind = find(Diff==0);
Right = numel(ind);
Wrong = numel(Y) - Right;
Accuracy = Right/(Right+Wrong);
disp(['Accuracy on testing set is: ' num2str(Accuracy*100) '%']);
