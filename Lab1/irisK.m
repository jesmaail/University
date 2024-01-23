load fisheriris
irisFeatures = {'Sepal Length'; 'Sepal Width'; 'Petal Length'; 'Petal Width'};
figure %opens the window
gplotmatrix(meas, meas, species, [], [], [], 'off', '', irisFeatures, irisFeatures) %plots it

X = meas(:,3:4);
k=3;
[idx,C]=kmeans(X,k,'Start', 'sample');

figure;
subplot(1,2,1);

hold on; %Holds the previous plot, stops from overwriting
gscatter(X(:,1),X(:,2),species);
title 'Truth'
xlabel 'Petal length'
ylabel 'Petal width'
subplot(1,2,2);
hold on;
gscatter(X(:,1), X(:,2), idx)
plot(C(:,1),C(:,2),'kx', 'MarkerSize', 15, 'LineWidth', 3) %highlight centroids
legend('Cluster 1', 'Cluster 2', 'Cluster 3', 'Centroids', 'Location', 'NW')
title 'K-means Clustering'
xlabel 'Petal Length'
ylabel 'Petal Width'

X = meas(:, [2,3,4]);
k=3;
[idx, C] = kmeans(X, k, 'Start', 'sample');

figure; %open a new figure
subplot(1,2,1)
hold on

h= gscatter(X(:,1), X(:,2),species);
gu=unique(species);
for igu=1 : numel(gu)
    set(h(igu), 'ZData', X(strcmp(species,gu(igu)),3));
end

view([-40, 40])
title 'Truth'
xlabel 'Sepal Width'
ylabel 'Petal Length'
zlabel 'Petal Width'

subplot(1,2,2)
hold on

h=gscatter(X(:,1),X(:,2),idx);
gu=unique(idx);
for igu=1 : numel(gu)
    set(h(igu), 'ZData', X(idx == gu(igu),3));
end
plot3(C(:,1),C(:,2),C(:,3), 'kx', 'MarkerSize', 15, 'LineWidth', 3);
view([-40,40])
title 'Cluster Assignments and Centroids'
xlabel 'Sepal Width'
ylabel 'Petal Length'
zlabel 'Petal Width'
