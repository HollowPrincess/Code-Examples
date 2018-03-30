function  Pictures( varargin )
%Здесь представлены графики поверхностей

close all;

%Функция 1: f1(x)=100*(x2-x1^2)^2+5*(1-x1)^2
% Пусть х1=х, х2=у, f1=z

[X,Y]=meshgrid(-5:0.5:5, -4:0.5:4);
Z=100*((Y-X.^2).^2)+5*((1-X).^2);
figure('Color','w')
hS=mesh(X,Y,Z);
xlabel('x');
ylabel('y');
zlabel('z')

% f2(x)=(x1^2+x2-11)^2+(x1+x2^2-7)^2

[X,Y]=meshgrid(-7:0.05:7, -7:0.05:7);
Z=(X.^2+Y-11).^2+(X+Y.^2-7).^2;
figure('Color','w')
hS=mesh(X,Y,Z);
xlabel('x');
ylabel('y');
zlabel('z')

end

