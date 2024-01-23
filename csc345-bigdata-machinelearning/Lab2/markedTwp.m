% Load the data
[X,Y] = wine_dataset;
X_t = X';

% Y will require orientating correctly as with labsheet one
[~, Y] = find(Y');

% Divide the dataset into a training and testing class
idx = crossvalind('Kfold',Y,2);
X_trn = X_t(idx==1,:);
Y_trn = Y(idx==1,:);
X_tst = X_t(idx==2,:);
Y_tst = Y(idx==2,:);

% Create LDA model of training set
figure;
h = gscatter(X_trn(:,1),X_trn(:,2),Y_trn);
%legend(unique(Y_trn));
hold on

ldaModel = fitcdiscr(X_trn, Y_trn);

newPoint = mean(X_trn);

scatter(newPoint(:,1),newPoint(:,2),'kx')

% Get the predictions of the model on the testing set
hold off
figure;
h1 = gscatter(X_tst(:,1),X_tst(:,2),Y_tst);
%ldaModel = fitcdiscr(X_tst, Y_tst);
hold on
newPoint = mean(X_tst);
scatter(newPoint(:,1),newPoint(:,2),'kx')


predictedClass = predict(ldaModel,newPoint)