clear
close all
clc

load fisheriris;
X = meas(:,[3,4]);
h = gscatter(X(:,1),X(:,2),species);
legend(unique(species));
hold on


ldaModel = fitcdiscr(X,species);

newPoint = mean(X);

scatter(newPoint(:,1),newPoint(:,2),'kx')


% Coefficients for boundary between classes 2 and 3
K = ldaModel.Coeffs(2,3).Const;
L = ldaModel.Coeffs(2,3).Linear;
% Plot the curve of the boundary
f = @(x1,x2) K + L(1)*x1 + L(2)*x2;
h2 = ezplot(f,[.9 7.1 0 2.5]);

% Coefficients for boundary between classes 1 and 2
K = ldaModel.Coeffs(1,2).Const;
L = ldaModel.Coeffs(1,2).Linear;
% Plot the curve of the boundary
f = @(x1,x2) K + L(1)*x1 + L(2)*x2;
h3 = ezplot(f,[.9 7.1 0 2.5]);


predictedClass = predict(ldaModel,newPoint)