function WordClick( varargin )
% Смена букв
global COUNTERTEXTVAR;
global Answer;
global tmpAnswer;
p1=varargin{3};
x=get(p1,'XData');

delete (Answer{x}) ;
Alp={' ','А', 'Б', 'В ', 'Г ', 'Д ', 'Е ', 'Ё', 'Ж','З','И','Й','К','Л','М','Н','О','П','Р','С','Т','У','Ф','Х','Ц','Ч','Щ','Ь','Ы','Ъ','Э','Ю','Я'};

Answer{x}=text(get(p1,'XData')-0.45,get(p1,'YData')+0.04,Alp{rem(COUNTERTEXTVAR{x}, length(Alp))+1});

set(Answer{x},'FontSize',50);

tmpAnswer{x}=Alp{rem(COUNTERTEXTVAR{x}, length(Alp))+1};
COUNTERTEXTVAR{x}=COUNTERTEXTVAR{x}+1;
EndProove()
end

function EndProove( varargin )
%Проверка на ответ

global rightAnswer;
global tmpAnswer;
flag=true;
for counter=1:length(rightAnswer)
    if tmpAnswer{counter}~=rightAnswer{counter}
        flag=false;
        break;
    end
end
if flag==true
    TheEndFunction()
end
end
function TheEndFunction( varargin )
%Правильно

endText=text(0.5, 0.9 ,'Правильно, нажмите для продолжения:' );
set(endText,'FontSize',15,'Color', 'w');
x=3;
y=0.5;

Next = plot(x,y);
set (Next ,'MarkerSize',30, 'Marker', 's','Color','c','MarkerFaceColor', 'c');
argCB ={@RandomWord, Next};
set(Next, 'ButtonDownFcn',argCB);

NextNext=plot(x,y);
set (NextNext ,'MarkerSize',15, 'Marker', '>','Color','k','MarkerFaceColor', 'k');
set(NextNext, 'ButtonDownFcn',argCB);

end


