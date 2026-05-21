#import "@local/typst-bsuir-core:1.1.1": *

// =====================================================================
// БАЗОВЫЕ НАСТРОЙКИ (ШРИФТЫ И ШАБЛОН)
// =====================================================================
#set text(font: "Times New Roman", size: 14pt, lang: "ru")
#show math.equation: set text(font: "STIX Two Math", size: 14pt)

#show: gost.with(
  title-template: custom-title-template.from-module(studing-practice-project-title),
  work: (
    type: "Отчет",
    subject: "по учебной практике (ознакомительной)\nпо теме\nИНФОРМАЦИОННАЯ СИСТЕМА АЭРОПОРТА",
  ),
  student: (
    name: "Минкевич А. С.",
    group: "558301"
  ),
  manager: (
    name: "Ковальчук А. М.",
    title: "старший преподаватель"
  ),
  year: none,
  footer: (city: "МИНСК", year: "2026"),
  pagination-align: right 
)

// Принудительно задаем поля по ГОСТу (левое 30, правое 15, верх/низ 20)
#set page(margin: (left: 30mm, right: 15mm, top: 20mm, bottom: 20mm))

// =====================================================================
// НАСТРОЙКИ АБЗАЦЕВ И ИНТЕРВАЛОВ
// =====================================================================
#set par(justify: true, first-line-indent: 1.25cm, leading: 0.65em, spacing: 0.65em)
#set list(indent: 1.25cm, body-indent: 0.5em)
#set enum(indent: 1.25cm, body-indent: 0.5em)

#show math.equation: it => {
  show ".": ","
  if it.block { pad(y: 0.5em, it) } else { it }
}
#set math.equation(numbering: none)

// =====================================================================
// НАСТРОЙКИ ЗАГОЛОВКОВ (ГОСТ)
// =====================================================================
#set heading(numbering: "1.1")

#show heading: it => {
  if it.level == 1 { pagebreak(weak: true) } else { v(14pt, weak: true) }
  
  set text(weight: "bold", size: 14pt)
  set par(first-line-indent: 0pt) 
  
  if it.level == 1 {
    if it.numbering == none {
      align(center)[#upper(it.body)]
    } else {
      align(left)[#h(1.25cm)#counter(heading).display(it.numbering) #upper(it.body)]
    }
  } else {
    align(left)[#h(1.25cm)#counter(heading).display(it.numbering) #it.body]
  }
  
  v(14pt, weak: true)
}

// =====================================================================
// НАСТРОЙКИ РИСУНКОВ И ТАБЛИЦ
// =====================================================================
#show heading.where(level: 1): it => {
  counter(figure.where(kind: image)).update(0)
  counter(figure.where(kind: table)).update(0)
  it
}

#show figure.where(kind: image): set figure(
  numbering: n => numbering("1.1", counter(heading).get().first(), n),
  gap: 14pt
)
#show figure.where(kind: image): set align(center)
#show figure.caption.where(kind: image): it => {
  set align(center)
  set par(first-line-indent: 0pt)
  set text(weight: "regular")
  [Рисунок ] + it.counter.display(it.numbering) + [ – ] + it.body
}

#show figure.where(kind: table): set figure(
  numbering: n => numbering("1.1", counter(heading).get().first(), n),
  gap: 14pt
)
#show figure.where(kind: table): set figure.caption(position: top)
#show figure.where(kind: table): set par(first-line-indent: 0pt) 

#show figure.caption.where(kind: table): it => {
  set align(left)
  set par(first-line-indent: 0pt) 
  set text(weight: "regular")
  [Таблица ] + it.counter.display(it.numbering) + [ – ] + it.body
}

// =====================================================================
// МАКРОС ДЛЯ ПРИЛОЖЕНИЙ
// =====================================================================
#let appendix(letter, title) = {
  pagebreak(weak: true)
  align(center)[
    #text(weight: "bold")[ПРИЛОЖЕНИЕ #letter]\
    (обязательное)\
    #text(weight: "bold")[#title]
  ]
  v(14pt)
}

// =====================================================================
// НАЧАЛО ДОКУМЕНТА
// =====================================================================

#heading(numbering: none, outlined: false)[СОДЕРЖАНИЕ]
#outline(title: none, depth: 2, indent: auto)

#heading(numbering: none)[УСЛОВИЕ ЗАДАНИЯ]

Напісаць праграму для кіравання інфармацыяй аб авіярэйсах аэрапорта. Праграма павінна выдаваць даведку пра маршрут, гэта значыць час рэйса, статус, тэрмінал і мадэль самалёта. Сістэма павінна дазваляць дадаваць, рэдагаваць і выдаляць рэйсы (з магчымасцю адмены апошняга дзеяння). 

Для забеспячэння хуткага пошуку па нумары рэйса неабходна выкарыстоўваць бінарнае дрэва пошуку (BST). Для часовага захавання рэйсаў перад іх пацвярджэннем павінна выкарыстоўвацца структура "чарга" (Queue), а для гісторыі змяненняў — "стэк" (Stack). Інфармацыя павінна захоўвацца ў тэкставых і бінарных файлах.

#heading(numbering: none)[ВВЕДЕНИЕ]

Аўтаматызацыя працэсаў уліку і маніторынгу авіярэйсаў з'яўляецца важнай задачай для любога сучаснага аэрапорта. Для забеспячэння хуткай працы і аптымальнага выкарыстання сістэмных рэсурсаў такія праграмныя прадукты патрабуюць дбайнага праектавання структур дадзеных і алгарытмаў апрацоўкі інфармацыі.

Мэтай дадзенай працы з'яўляецца распрацоўка кансольнага прыкладання на мове праграмавання C, якое рэалізуе базавы функцыянал інфармацыйнага табло аэрапорта з гнуткай сістэмай фільтрацыі і пошуку.

Для дасягнення пастаўленай мэты неабходна вырашыць наступныя задачы: спраектаваць структуры дадзеных для захоўвання інфармацыі пра рэйсы; рэалізаваць дынамічныя структуры дадзеных (стэк, чаргу і бінарнае дрэва пошуку); распрацаваць сістэму захавання і загрузкі базы дадзеных з выкарыстаннем тэкставага і бінарнага файлавага ўводу-вываду; рэалізаваць кансольны карыстальніцкі інтэрфейс з размеркаваннем правоў доступу.

У першым раздзеле тлумачальнай запіскі праводзіцца праектаванне структур дадзеных. У другім раздзеле апісваецца працэс распрацоўкі алгарытмаў і праграмных модуляў. Трэці раздзел прысвечаны дэманстрацыі вынікаў работы праграмы.

= ФУНКЦИОНАЛЬНОЕ ПРОЕКТИРОВАНИЕ

== Входные и выходные данные

Для захоўвання інфармацыі ў дадатку распрацавана іерархічная мадэль дадзеных. У табліцы 1.1 прадстаўлены склад і ўкладзенасць структур, якія выкарыстоўваюцца для апісання рэйсаў і ўсёй сістэмы аэрапорта.

#figure(
  table(
    columns: 4, 
    align: left + horizon,

    table.header(
      table.cell(colspan: 4, align: center)[*Структуры і тыпы дадзеных*]
    ),

    table.cell(rowspan: 2)[*enum FlightType*],
    table.cell(colspan: 3)[ARRIVAL (0)],
    table.cell(colspan: 3)[DEPARTURE (1)],

    table.cell(rowspan: 4)[*enum FlightStatus*],
    table.cell(colspan: 3)[ON_TIME, DELAYED],
    table.cell(colspan: 3)[BOARDING, DEPARTED],
    table.cell(colspan: 3)[LANDED, CANCELED],
    table.cell(colspan: 3)[(Цэлалікавыя значэнні ад 0 да 5)],

    table.cell(rowspan: 2)[*struct DateTime*],
    table.cell(colspan: 3)[int day, month, year],
    table.cell(colspan: 3)[int hour, minute],

    table.cell(rowspan: 6)[*struct Flight*],
    table.cell(colspan: 3)[char flightNumber[10]],
    table.cell(colspan: 3)[char airline[50], city[50]],
    table.cell(colspan: 3)[FlightType type],
    table.cell(colspan: 3)[DateTime scheduleTime, actualTime],
    table.cell(colspan: 3)[FlightStatus status],
    table.cell(colspan: 3)[char terminal, int gate],

    table.cell(rowspan: 2)[*struct StackNode*],
    table.cell(colspan: 3)[Flight data],
    table.cell(colspan: 3)[struct StackNode\* next],

    table.cell(rowspan: 2)[*struct QueueNode*],
    table.cell(colspan: 3)[Flight data],
    table.cell(colspan: 3)[struct QueueNode\* next],

    table.cell(rowspan: 3)[*struct TreeNode*],
    table.cell(colspan: 3)[Flight data],
    table.cell(colspan: 3)[struct TreeNode\* left],
    table.cell(colspan: 3)[struct TreeNode\* right],

    table.cell(rowspan: 6)[*struct AirportSystem*],
    table.cell(colspan: 3)[Flight flights[MAX_FLIGHTS]],
    table.cell(colspan: 3)[int count],
    table.cell(rowspan: 2)[*Stack history*],
    table.cell(colspan: 2)[StackNode\* top],
    table.cell(colspan: 2)[int size],
    table.cell(rowspan: 2)[*Queue pendingQueue*],
    table.cell(colspan: 2)[QueueNode\* head, tail],
    table.cell(colspan: 2)[int size],
    table.cell(colspan: 3)[TreeNode\* searchTree]
  ),
  caption: [Іерархія і склад структур дадзеных дадатку]
) <data-structures>

= РАЗРАБОТКА ПРОГРАММНЫХ МОДУЛЕЙ

== Разработка схем алгоритмов

Схема алгарытму асноўнай праграмы прадстаўлена ў дадатку А. Яна ўключае цыкл аўтэнтыфікацыі і пераход да галоўнага меню.

Функцыя `sys_delete_flight` дазваляе бяспечна выдаляць рэйсы з захаваннем стану ў стэку для наступнай адмены (схема прадстаўлена ў дадатку Б).

Функцыя `sys_sort_by_schedule` дазваляе сартаваць масіў рэйсаў па часе метадам устаўкі (схема алгарытму прадстаўлена ў дадатку В).

== Разработка алгоритмов

Функцыя `sys_delete_flight` выконвае выдаленне элемента з масіва сістэмы з папярэднім захаваннем стану ў стэк гісторыі і выдаленнем адпаведнага вузла з бінарнага дрэва пошуку.

Перадаваемыя параметры: \
`sys` — указальнік на структуру сістэмы (`AirportSystem`). \
`idx` — цэлалікавае значэнне індэкса рэйса для выдалення. \
Крок 1. Пачатак. \
Крок 2. Аб’явіць лакальную зменную `i` (цэлага тыпу) для параметру цыклу. \
Крок 3. Калі індэкс `idx` меншы за 0 або большы/роўны значэнню `sys->count`, перарваць выкананне функцыі. \
Крок 4. Выклікаць функцыю `stack_push(&sys->history, sys->flights[idx])` для захавання бягучага стану рэйса ў гісторыю. \
Крок 5. Прысвоіць зменнай `sys->searchTree` вынік выканання функцыі `bst_delete`. \
Крок 6. Цыкл з параметрам `i` ад значэння `idx` да `sys->count - 1`. \
Крок 7. Прысвоіць элементу масіва `sys->flights[i]` значэнне наступнага элемента масіва `sys->flights[i + 1]`. \
Крок 8. Канец цыклу па `i`. \
Крок 9. Паменшыць значэнне зменнай `sys->count` на 1. \
Крок 10. Канец.

Функцыя `sys_sort_by_schedule` выконвае сартаванне масіва рэйсаў па часе вылету/прылёту (`scheduleTime`) з выкарыстаннем алгарытму сартавання ўстаўкай.\
Крок 1. Пачатак. \
Крок 2. Аб'явіць лакальныя зменныя `i` і `j` (цэлага тыпу) для цыклаў, а таксама `key` (структура тыпу `Flight`) для часовага захавання элемента. \
Крок 3. Цыкл з параметрам `i` ад 1 да `sys->count`. \
Крок 4. Прысвоіць зменнай `key` значэнне элемента масіва `sys->flights[i]`. \
Крок 5. Прысвоіць зменнай `j` значэнне выразу `i - 1`. \
Крок 6. Цыкл пакуль `j >= 0` і функцыя `datetime_compare(...)` вяртае лік, большы за 0. \
Крок 7. Прысвоіць элементу `sys->flights[j + 1]` значэнне `sys->flights[j]`. \
Крок 8. Паменшыць значэнне зменнай `j` на 1. \
Крок 9. Канец цыклу пакуль. \
Крок 10. Прысвоіць элементу масіва `sys->flights[j + 1]` значэнне зменнай `key`. \
Крок 11. Канец цыклу па `i`. \
Крок 12. Канец.

= РЕЗУЛЬТАТ РАБОТЫ

Ніжэй прыведзены скрыншоты, якія дэманструюць асноўны функцыянал распрацаванага дадатку.

#figure(
  block(width: 80%, height: 150pt, stroke: 1pt, align(center + horizon)[Месца для скрыншота: Аўтэнтыфікацыя і галоўнае меню]),
  caption: [Галоўнае меню праграмы]
)

#figure(
  block(width: 80%, height: 150pt, stroke: 1pt, align(center + horizon)[Месца для скрыншота: Даданне рэйса праз кансоль]),
  caption: [Увод інфармацыі аб новым рэйсе]
)

#figure(
  block(width: 90%, height: 180pt, stroke: 1pt, align(center + horizon)[Месца для скрыншота: Вывад табліцы рэйсаў]),
  caption: [Вывад поўнага спіса рэйсаў у выглядзе табліцы]
)

#figure(
  block(width: 80%, height: 150pt, stroke: 1pt, align(center + horizon)[Месца для скрыншота: Вынікі пошуку]),
  caption: [Пошук па фільтрах у сістэме]
)

#heading(numbering: none)[ЗАКЛЮЧЕНИЕ]

Падчас выканання практыкі была паспяхова распрацавана кансольная інфармацыйная сістэма аэрапорта. Дадатак дае карыстальнікам дакладную інфармацыю пра час рэйсаў, статусы вылетаў і прылётаў, нумары тэрміналаў і мадэлі самалётаў.

Праграма мае зручны і зразумелы інтэрфейс, які падзяляе правы доступу паміж пасажырамі і адміністратарамі. Выкарыстанне дынамічных структур дадзеных (бінарнае дрэва пошуку, стэк для гісторыі адмен і чарга для чакаючых рэйсаў) значна павысіла эфектыўнасць апрацоўкі інфармацыі.

Асаблівая ўвага пры распрацоўцы была нададзена надзейнасці ўводу дадзеных і бяспечнай працы з памяццю. Файлавы ўвод-вывад дазваляе бяспечна захоўваць базу дадзеных паміж сесіямі ў розных фарматах.

У выніку выканання праекта былі не толькі замацаваны навыкі праграмавання на мове C, але і атрыманы каштоўны вопыт стварэння рэальнага прыкладання для працы з транспартнымі маршрутамі і складанымі структурамі дадзеных.

#heading(numbering: none)[СПИСОК ИСПОЛЬЗОВАННЫХ ИСТОЧНИКОВ]

[1] Основы алгоритмизации и программирования : лаборатор. практикум для студентов специальности 1-40 02 01 «Вычисл. машины, системы и сети» всех форм обучения. В 2 ч. Ч. 2 / сост. Ю. А. Луцик [и др.]. – Минск : БГУИР, 2010. – 36 с. : ил.

[2] Шилдт, Г. C: полное руководство, 4-е издание / Г. Шилдт. – М. : Вильямс, 2011. – 704 с.

[3] StackOverflow [Электронный ресурс] – Вопросы – режим доступа: https://ru.stackoverflow.com.
// =====================================================================
// СПИСОК ИСПОЛЬЗОВАННЫХ ИСТОЧНИКОВ
// =====================================================================
#heading(numbering: none)[СПИСОК ИСПОЛЬЗОВАННЫХ ИСТОЧНИКОВ]

[1] Основы алгоритмизации и программирования : лаборатор. практикум для студентов специальности 1-40 02 01 «Вычисл. машины, системы и сети» всех форм обучения. В 2 ч. Ч. 2 / сост. Ю. А. Луцик [и др.]. – Минск : БГУИР, 2010. – 36 с. : ил.

[2] Шилдт, Г. C: полное руководство, 4-е издание / Г. Шилдт. – М. : Вильямс, 2011. – 704 с.

[3] StackOverflow [Электронный ресурс] – Вопросы – режим доступа: https://ru.stackoverflow.com.

// =====================================================================
// ПРИЛОЖЕНИЯ
// =====================================================================

// Импортируем вашу библиотеку для рамок ЕСКД
#import "frames/template.typ": eskd-scheme

// Отключаем красную строку для блоков кода и картинок в приложениях
#set par(first-line-indent: 0pt)


// === ПРИЛОЖЕНИЕ А ===
#appendix("А", "Схема алгоритма программы main")

#eskd-scheme(
  title: "Блок-схема функции\nmain",
  doc-code: "ГУИР.6-05-0611-05.420", 
  dev-name: "Минкевич",
  prov-name: "Ковальчук",
  group-name: "ЭВМ, гр. 558301",
  paper-format: "a4",
  vertical: true
)[
  // Блок на всю доступную ширину/высоту внутри отступов рамки
  #block(width: 110%, height: 100%)[
    #align(center + horizon)[
      // Используем SVG для абсолютной четкости текста и линий!
      // Если все же используете PNG, убедитесь, что его разрешение от 2000x3000 пикселей.
      #image("blochka_main2.svg", width: 100%, height: 100%, fit: "contain")
    ]
  ]
]


// === ПРИЛОЖЕНИЕ Б ===
#appendix("Б", "Схема алгоритма функции sys_delete_flight")

#eskd-scheme(
  title: "Блок-схема функции\nsys_delete_flight",
  doc-code: "ГУИР.6-05-0611-05.420",
  dev-name: "Минкевич",
  prov-name: "Ковальчук",
  group-name: "ЭВМ, гр. 558301",
  paper-format: "a4",
  vertical: true
)[
  #block(width: 100%, height: 100%)[
    #align(center + horizon)[
      #image("blochka_delete2.svg", width: 100%, height: 105%, fit: "contain")
    ]
  ]
]


// // === ПРИЛОЖЕНИЕ В ===
// #appendix("В", "Схема алгоритма функции sys_sort_by_schedule")

// #eskd-scheme(
//   title: "Блок-схема функции\nsys_sort_by_schedule",
//   doc-code: "ГУИР.6-05-0611-05.420",
//   dev-name: "Минкевич",
//   prov-name: "Ковальчук",
//   group-name: "ЭВМ, гр. 558301",
//   paper-format: "a4",
//   vertical: true
// )[
//   #block(width: 100%, height: 100%)[
//     #align(center + horizon)[
//       #image("sys_sort_by_schedule.svg", width: 100%, height: 100%, fit: "contain")
//     ]
//   ]
// ]


// === ПРИЛОЖЕНИЕ Г ===
#appendix("Г", "Код файла main.c")

#set text(size: 10pt, font: "Courier New")
```
// Праграма "Аэрапорт": сістэма кіравання рэйсамі.
#include "header.h"

int main(void)
{
    AirportSystem sys;
    sys_init(&sys);

    printf("==========================================\n");
    printf("      AIRPORT INFORMATION SYSTEM v1.0    \n");
    printf("==========================================\n\n");

    User currentUser;
    int  attempts = 0;
    while (!auth_login(&currentUser))
    {
        attempts++;
        if (attempts >= 3)
        {
            printf("  Too many failed attempts. Exiting.\n");
            sys_free(&sys);
            return 1;
        }
    }

    input_choose(&sys);
    menu_main(&sys, &currentUser);

    sys_free(&sys);
    return 0;
}
```