function newton (num)
clc;
close all;
hold on
syms dzdx(X,Y);
syms dzdy(X,Y);
syms d2zdx2(X,Y);
syms d2zdxdy(X,Y);
syms d2zdydx(X,Y);
syms d2zdy2(X,Y);
syms myGradient(X,Y);
syms grasian(X,Y);
syms Z(X,Y);

%Функция 1: f1(x)=100*(x2-x1^2)^2+5*(1-x1)^2
%Функция 2: f2(x)=(x1^2+x2-11)^2+(x1+x2^2-7)^2
% Пусть х1=х, х2=у, f1=z
%   Необходимое условие: дифференцируемость второго порядка

switch num
    case 1
        
        Z=100*((Y-X.^2).^2)+5*((1-X).^2)
        dzdx=diff(Z,X);
        dzdy=diff(Z,Y);
        d2zdx2=diff(dzdx,X);
        d2zdxdy=diff(dzdx,Y);
        d2zdydx=diff(dzdy,X);
        d2zdy2=diff(dzdy,Y);
        myGradient =[dzdx, dzdy]
        grasian =[d2zdx2,d2zdxdy;d2zdydx,d2zdy2]
        
        [x,y]=meshgrid(-5:0.05:5, -4:0.5:4);
        z=100*((y-x.^2).^2)+5*((1-x).^2);
        
        doNewton([4,0], Z,myGradient, grasian);
        
    case 2
        
        Z=(X.^2+Y-11).^2+(X+Y.^2-7).^2
        dzdx=diff(Z,X);
        dzdy=diff(Z,Y);
        d2zdx2=diff(dzdx,X);
        d2zdxdy=diff(dzdx,Y);
        d2zdydx=diff(dzdy,X);
        d2zdy2=diff(dzdy,Y);
        myGradient =[dzdx,dzdy]
        grasian =[d2zdx2,d2zdxdy;d2zdydx,d2zdy2]
                
        [x,y]=meshgrid(-7:0.05:7, -7:0.05:7);
        z=(x.^2+y-11).^2+(x+y.^2-7).^2;
        
        doNewton([2,2],Z,myGradient, grasian);
        doNewton([-4,-4],Z,myGradient, grasian);
        doNewton([6,6],Z,myGradient, grasian);
        doNewton([-2,2],Z,myGradient, grasian);
        
end
hS=mesh(x,y,z);
xlabel('x');
ylabel('y');
zlabel('z');

end
function  doNewton( previousDot, Z,myGradient, grasian )
counter=0;

syms functionNorma(X,Y);
% Необходимые константы
% Погрешность. Внимание! Её значения должны быть в интервале (0,1).
epsilon = 0.05;
functionNorma=sqrt((myGradient(1))^2 + (myGradient(2))^2);

dot=previousDot;
X=dot(1);
Y=dot(2);
while (eval(functionNorma) >= epsilon) 
    counter=counter+1;
    invGrasian=inv(eval(grasian));
    dot=previousDot-(invGrasian*(eval(myGradient).')).';
    X=dot(1);
    Y=dot(2);
    previousDot=dot;
end
%  точка
counter
X=[X]
Y=[Y]
Z=[eval(Z)]

plot3 (X,Y,Z,'*k');

end
