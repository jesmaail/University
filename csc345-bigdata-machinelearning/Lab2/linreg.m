clear
close all
clc

X = 0.1:0.1:1;
Y_True = 1.2 + 3.25 * X;
Y_Observation = Y_True + 0.5*normrnd(0,0.5,1,numel(X));



h1 = figure;
hold on;
% plot true function in green
plot(-0.2:0.1:1.2, 1.2+3.25*(-0.2:0.1:1.2), '-g', 'LineWidth', 2);
% plot observation of Y in blue
plot(X, Y_Observation, 'ob', 'MarkerSize', 10, 'LineWidth', 2);
% plot the distance between the observations and the true values
plot([X;X], [Y_True;Y_Observation], '-c', 'LineWidth', 2);
xlim([-0.2, 1.2]);
ylim([-1, 5]);
hold off;



w0 = 2*rand(); %make the value close to the true w0
w1 = 6*rand(); %make the value close to the true w1
% learning speed control parameter
alpha = 0.5; % change the value of learning speed to see the difference
% gradient descent, you can have a much better stopping criterion
disp('->Gradient Descent');
h2 = figure;
for i = 1:200 % change the number of search step to see the difference
    % the value of the model with the parameters w0 and w1
    Y_Fit = w0 + w1*X;
    % the difference between the observations and the value given by the model
    Y_Dif = Y_Fit - Y_Observation;
    % the partial dirivative of mean squares of error with respect to w0
    PD_MSE_W0 = sum(Y_Dif.*1);
    % update the w0
    w0 = w0 - alpha*PD_MSE_W0/numel(Y_Observation);

    % the partial dirivative of mean squares of error with respect to w1
    PD_MSE_W1 = sum(Y_Dif.*X);
    % update the w1
    w1 = w1 - alpha*PD_MSE_W1/numel(Y_Observation);

    % display the message and plot the graph every 10 runs
    MSE = mean(((w0 + w1*X) - Y_Observation).^2);
    if mod(i,10) == 0
        disp(['->->Itor: ' num2str(i) ' Update w0 = ' num2str(w0) ' w1 = ' num2str(w1) ' MSError = ' num2str(MSE)]);
        figure(h2);
        cla;
        hold on;
        % plot true function in green
        plot(-0.2:0.1:1.2, 1.2+3.25*(-0.2:0.1:1.2), '-g', 'LineWidth', 2);
        % plot the fitted function in green
        plot(-0.2:0.1:1.2, w0+w1*(-0.2:0.1:1.2), '-r', 'LineWidth', 2);
        % plot observation of Y in blue
        plot(X, Y_Observation, 'ob', 'MarkerSize', 10, 'LineWidth', 2);
        % plot the distance between the observations and the fitted values
        plot([X;X], [(w0 + w1*X);Y_Observation], '-c', 'LineWidth', 2);
        xlim([-0.2, 1.2]);
        ylim([-1, 5]);
        hold off;
%       pause(1); %uncomment this line to help with visualisation
    end
end
disp(['-->Model: w0 = ' num2str(w0) ' w1= ' num2str(w1) ' MSError = ' num2str(MSE)]);



mdl = fitlm(X,Y_Observation,'linear');
h3 = figure;
hold on;
plotAdded(mdl);
% plot true function in green
plot(-0.2:0.1:1.2, 1.2+3.25*(-0.2:0.1:1.2), '-g', 'LineWidth', 1);
hold off;
disp(['-->Model: w0 = ' num2str(mdl.Coefficients{1,1}) ' w1= ' num2str(mdl.Coefficients{2,1}) ' MSError = ' num2str(mdl.MSE)]);