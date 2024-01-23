clear;
close all;
clc;
rng(4);
[X,Y] = wine_dataset;
X_t = X';
[~, Y] = find(Y');

%X = meas(:,1:2); %select features to for GMM over peta meausurements
%[n,p] - size(X);

%plot the data in the feature space
figure;
gscatter(X_t(:,1),X_t(:,2),Y);
title('Wine Data Set');
xlabel('Alcohol');
ylabel('Malic Acid');

%GMM tuning params
k = 3;
options = statset('MaxIter', 1000); %increase no. of EM iterations

%plotting params
d = 500;
x1 = linspace(min(X_t(:,1)) - 2,max(X_t(:,1)) + 2,d);
x2 = linspace(min(X_t(:,2)) - 2,max(X_t(:,2)) + 2,d);
[x1grid,x2grid] = meshgrid(x1,x2);
X0 = [x1grid(:) x2grid(:)]; % create points that cover the data space of interest
threshold = sqrt(chi2inv(0.99,2)); % select Gaussian with 99% confidence
plotColors = [0.5,0.5,0.5;0.62,0.62,0.62;0.87,0.87,0.87;0.75,0.75,0.75];
c = 1;
figure()

% Fit gaussian and plot
for ik = 1 : k
    % fit ik Gaussian mixtures
    gmModel = fitgmdist(X_t,ik,'Options',options);
    clusterX = cluster(gmModel, X_t);
    % plot Gaussians over truth
    mahalDist = mahal(gmModel,X_t);
    subplot(2,2,c);
    h1 = gscatter(X_t(:,1),X_t(:,2),clusterX,'rbgm'); % plot truth
    hold on;
    for m = 1:ik;
        idx = mahalDist(:,m)<=threshold; %find coverage fo 99% for Gaussian |m|
        h2 = plot(X_t(idx,1),X_t(idx,2),'.','Color',plotColors(m,:),'MarkerSize',1);
        uistack(h2,'bottom');
    end
    plot(gmModel.mu(:,1),gmModel.mu(:,2),'kx','LineWidth',2,'MarkerSize',10)
    %axis([4,8,1.5,5.5])
    hold off
    c = c + 1;
end