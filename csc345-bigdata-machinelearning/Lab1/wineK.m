clear;
close all;
clc;

[X,Y] = wine_dataset;
X_t = X';
[~, Y] = find(Y'); %orientate Y and turn into a label ID matrix.

wineFeatures = {'Alcohol'; 'Malic acid'; 'Ash'; 'Alcal. of ash'; 'Magnesium'; 'Total phenols';
    'Flavanoids'; 'Nonflava. phenols'; 'Proanthocyanins'; 'Col. intensity'; 'Hue'; 'OD280/OD315'; 'Proline'};
%figure %opens the window
%gplotmatrix(X_t, X_t, Y, [], [], [], 'off', '', wineFeatures, wineFeatures) %plots it


%Start Figure 2

k=3;
[idx,C]=kmeans(X_t(:,[1,2]), k, 'Start', 'sample');

figure;
subplot(2, 2, 1);
hold on; %Holds the previous plot, stops from overwriting
gscatter(X_t(:,1),X_t(:,2), Y);
title 'Truth'
xlabel 'Alcohol'
ylabel 'Malic Acid'

subplot(2, 2, 2);   
hold on;
gscatter(X_t(:,1), X_t(:,2), idx)
plot(C(:,1),C(:,2),'kx', 'MarkerSize', 15, 'LineWidth', 3) %highlight centroids
legend('Cluster 1', 'Cluster 2', 'Cluster 3', 'Centroids', 'Location', 'NW')
title 'K-means Clustering'
xlabel 'Alcohol'
ylabel 'Malic Acid'

[idx, C]=kmeans(X_t(:,[7,12]), k, 'Start', 'sample');

subplot(2, 2, 3);
hold on;
gscatter(X_t(:,7),X_t(:,12), Y);
title 'Truth'
xlabel 'Flavanoids'
ylabel 'OD280/OD315 of diluted wines'


subplot(2, 2, 4);
hold on;
gscatter(X_t(:,7), X_t(:,12), idx)
plot(C(:,1),C(:,2),'kx', 'MarkerSize', 15, 'LineWidth', 3) %highlight centroids
legend('Cluster 1', 'Cluster 2', 'Cluster 3', 'Centroids', 'Location', 'NW')
title 'K-means Clustering'
xlabel 'Flavanoids'
ylabel 'OD280/OD315 of diluted wines'



k=3;
[idx, C] = kmeans(X_t, k, 'Start', 'sample');




figure; %open a new figure
subplot(1,2,1)
hold on

h= gscatter(X_t(:,1), X_t(:,2),Y);
gu=unique(Y);
for igu=1 : numel(gu)
    set(h(igu), 'ZData', X_t(strcmp(Y,gu(igu)),3));
end

view([-40, 40])
title 'Truth'
xlabel 'Alcohol'
ylabel 'Malic Acid'
zlabel 'Ash'

subplot(1,2,2)
hold on

h=gscatter(X_t(:,1),X_t(:,2),idx);
gu=unique(idx);
for igu=1 : numel(gu)
    set(h(igu), 'ZData', X_t(idx == gu(igu),3));
end
plot3(C(:,1),C(:,2),C(:,3), 'kx', 'MarkerSize', 15, 'LineWidth', 3);
view([-40,40])
title 'Cluster Assignments and Centroids'
xlabel 'Alcohol'
ylabel 'Malic Acid'
zlabel 'Ash'