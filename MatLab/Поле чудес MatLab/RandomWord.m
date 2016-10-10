function RandomWord( varargin )
%Поле Чудес
clc;
close all;
global QUESTION;
global Answer;
global COUNTERTEXTVAR;
global questionText;
global tmpAnswer;
global rightAnswer;


AskAQuestion(  );
maxX=length(rightAnswer);
y=2;

for x=1:maxX
    xlim([0 6])
    ylim([0 4])
    Answer{x}=text(x-0.45,y+0.04,' ');
    tmpAnswer{x}='-';
    COUNTERTEXTVAR{x}=1;
    
    p1 = plot(x,y);
    axis off;
    set(1, 'Color', [0 0 0]);
    
    set (p1 ,'MarkerSize',67.5, 'Marker', 's', 'Color', 'w', 'MarkerFaceColor', 'w');
    axis manual
    hold on
    
    p2 = plot(x,y-0.75);
    set (p2 ,'MarkerSize',20, 'Marker', 'd','Color', 'c','MarkerFaceColor', 'c');
    %     сброс буквы
    p3 = plot(x,y+0.75);
    set (p3 ,'MarkerSize',20, 'Marker', 'o','Color', 'r','MarkerFaceColor', 'r');
    argCBnone ={@WordClickNone,p1};
    set  (p3, 'ButtonDownFcn',argCBnone);
    
    argCB ={@WordClick, p1};
    
    set(p1, 'ButtonDownFcn',argCB);
    set(p2, 'ButtonDownFcn',argCB);
end
questionText=text(0.5, 3.5, QUESTION);
set(questionText,'FontSize',15, 'Color', 'w');
end
function AskAQuestion( varargin )
%Функция выдает вопрос, на который нужно дать ответ
global QUESTION;
global rightAnswer;
global QUESTIONCOUNTER;
QUESTIONCOUNTER;

questionCell=cell(1,2);
questionCell {1,1}= {'Кто автор высказывания: ';'«Краткость – сестра таланта»?'};
questionCell {3,1}= {'Кто изобрел MatLab?'};
questionCell {2,1}= {'Сколько раз переименовывали';' Cанкт-Петербург?'};
if isempty(QUESTIONCOUNTER)
    QUESTIONCOUNTER=1;
else
    QUESTIONCOUNTER=(rem((QUESTIONCOUNTER),length(questionCell)))+1;
end
QUESTION=questionCell{QUESTIONCOUNTER,1};

rightAnswerCell=cell(1,length(QUESTION));
rightAnswerCell{1,1} ={'Ч','Е','Х','О','В'};
rightAnswerCell{3,1} ={'М','О','Л','Е','Р'};
rightAnswerCell{2,1} ={'Т','Р','И'};


rightAnswer=rightAnswerCell{QUESTIONCOUNTER,1};
end

