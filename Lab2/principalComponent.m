clear
close all
clc

load('IMM.mat');
nPoints = 58;
nSamples = size(IMM,1);


h1 = figure;
hold on;
PTS = zeros(nSamples, nPoints*2);
for i = 1:nSamples
    tmp = IMM{i,3}(:,[3 4]);
    tmp(:,2) = 1-tmp(:,2);
    PTS(i,:) = tmp(:);
    if mod(i,20)==0
        figure(h1);
        plot(tmp(:,1),tmp(:,2), '.b');
    end
end
figure(h1);
hold off;
axis equal;

Mean_Face_NoAlign = reshape(mean(PTS),[58,2]);
figure(h1);
hold on;
plot(Mean_Face_NoAlign(:,1),Mean_Face_NoAlign(:,2), 'xr', 'MarkerSize', 10, 'LineWidth', 2);
plot(Mean_Face_NoAlign(1:13,1),Mean_Face_NoAlign(1:13,2), '-g', 'LineWidth', 2);
plot(Mean_Face_NoAlign([14:21,14],1),Mean_Face_NoAlign([14:21,14],2), '-g', 'LineWidth', 2);
plot(Mean_Face_NoAlign([22:29,22],1),Mean_Face_NoAlign([22:29,22],2), '-g', 'LineWidth', 2);
plot(Mean_Face_NoAlign(30:34,1),Mean_Face_NoAlign(30:34,2), '-g', 'LineWidth', 2);
plot(Mean_Face_NoAlign(35:39,1),Mean_Face_NoAlign(35:39,2), '-g', 'LineWidth', 2);
plot(Mean_Face_NoAlign([40:47,40],1),Mean_Face_NoAlign([40:47,40],2), '-g', 'LineWidth', 2);
plot(Mean_Face_NoAlign([48:58,48],1),Mean_Face_NoAlign([48:58,48],2), '-g','LineWidth', 2);
hold off;


h2 = figure;
hold on;
TPTS = zeros(nSamples, nPoints*2);
for i = 1:nSamples
    tmp = reshape(PTS(i,:),[58,2]);
    [~,tmp,~] = procrustes(Mean_Face_NoAlign,tmp);
    TPTS(i,:) = tmp(:);
    if mod(i,20)==0
        figure(h2);
        plot(tmp(:,1),tmp(:,2), '.b');
    end
end
figure(h2);
hold off;
axis equal;


[Evalues, Evectors, Mean_Face] = PCA(TPTS');
Mean_Face = reshape(Mean_Face, [58,2]);

figure(h2);
hold on;
plot(Mean_Face(:,1),Mean_Face(:,2), 'xr', 'MarkerSize', 10, 'LineWidth', 2);
plot(Mean_Face(1:13,1),Mean_Face(1:13,2), '-g', 'LineWidth', 2);
plot(Mean_Face([14:21,14],1),Mean_Face([14:21,14],2), '-g', 'LineWidth', 2);
plot(Mean_Face([22:29,22],1),Mean_Face([22:29,22],2), '-g', 'LineWidth', 2);
plot(Mean_Face(30:34,1),Mean_Face(30:34,2), '-g', 'LineWidth', 2);
plot(Mean_Face(35:39,1),Mean_Face(35:39,2), '-g', 'LineWidth', 2);
plot(Mean_Face([40:47,40],1),Mean_Face([40:47,40],2), '-g', 'LineWidth', 2);
plot(Mean_Face([48:58,48],1),Mean_Face([48:58,48],2), '-g','LineWidth', 2);
hold off;


h3 = figure;
for i = 1:10
    for j = -10:1:10
        newev = Evalues;
        newev(i) = newev(i)*(1+(j*3*i));
        Face = Mean_Face(:) + ((newev')*Evectors)';
        Face = reshape(Face, [58,2]);
        figure(h3);
        cla;
        hold on;
        plot(Mean_Face(:,1),Mean_Face(:,2), 'xr', 'MarkerSize', 10, 'LineWidth', 2);
        plot(Mean_Face(1:13,1),Mean_Face(1:13,2), '-g', 'LineWidth', 2);
        plot(Mean_Face([14:21,14],1),Mean_Face([14:21,14],2), '-g', 'LineWidth', 2);
        plot(Mean_Face([22:29,22],1),Mean_Face([22:29,22],2), '-g', 'LineWidth', 2);
        plot(Mean_Face(30:34,1),Mean_Face(30:34,2), '-g', 'LineWidth', 2);
        plot(Mean_Face(35:39,1),Mean_Face(35:39,2), '-g', 'LineWidth', 2);
        plot(Mean_Face([40:47,40],1),Mean_Face([40:47,40],2), '-g', 'LineWidth', 2);
        plot(Mean_Face([48:58,48],1),Mean_Face([48:58,48],2), '-g','LineWidth', 2);

        plot(Face(1:13,1),Face(1:13,2), '-b', 'LineWidth', 2);
        plot(Face([14:21,14],1),Face([14:21,14],2), '-b', 'LineWidth', 2);
        plot(Face([22:29,22],1),Face([22:29,22],2), '-b', 'LineWidth', 2);
        plot(Face(30:34,1),Face(30:34,2), '-b', 'LineWidth', 2);
        plot(Face(35:39,1),Face(35:39,2), '-b', 'LineWidth', 2);
        plot(Face([40:47,40],1),Face([40:47,40],2), '-b', 'LineWidth', 2);
        plot(Face([48:58,48],1),Face([48:58,48],2), '-b','LineWidth', 2);
        axis equal;
        xlim([0.3,0.7]);
        ylim([0.1,0.7]);
        hold off;
%         pause(0.2);
    end
end