clc
clear all
close all

data = load('SimulatorData.txt');

data2 = data(20000:end,:);

time = data(:,1);
thrust = data(:,2);
xpos = data(:,3);
xvel = data(:,4);
zpos = data(:,5);
zvel = data(:,6);
angularpos = data(:,7);
angularvel = data(:,8);
kex = data(:,9);
kez = data(:,10);
kea = data(:,11);

figure(1)
hold on
plot(xpos,zpos,'g.',data2(:,3),data2(:,5),'b.')

figure(2)
hold on
plot(xvel,zvel,'b.')

figure(1)






