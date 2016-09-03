clear all; close all; clc;

theta   = textread('theta.txt', '%f');
d_theta = textread('d_theta.txt', '%f');

theta_slope = (theta(end) - theta(1)) / length(theta);

%% Difference data

difference_theta = nan(1, length(theta)-1);

for i = 1:length(theta)-1
   
    difference_theta(i) = theta(i+1) - theta(i);
end
%% Plot

figure(1);
hold on; grid on;

plot(1:length(theta), theta, 'r');
plot(1:length(d_theta), d_theta, 'b');

l = legend('$\theta$', '$\dot{\theta}$');
set(l, 'Interpreter', 'latex');

figure(2);
hold on; grid on;

plot(1:length(difference_theta), difference_theta, 'k');