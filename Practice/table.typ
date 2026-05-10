#set text(font: "Times New Roman", size: 14pt, lang: "ru")
#set table(stroke: 0.5pt + black)

// ==========================================
// Табліца 1: DateTime
// ==========================================
#figure(
  table(
    columns: (1fr, 1fr, 2fr),
    align: (left, left, left),
    table.header([*Назва поля*], [*Тып дадзеных*], [*Апісанне*]),
    
    [`day`], [`int`], [Дзень],
    [`month`], [`int`], [Месяц],
    [`year`], [`int`], [Год],
    [`hour`], [`int`], [Гадзіны],
    [`minute`], [`int`], [Хвіліны],
  ),
  caption: [Структура DateTime (Захоўванне часу і даты)]
)

// ==========================================
// Табліца 2: Flight
// ==========================================
#figure(
  table(
    columns: (1.2fr, 1.2fr, 2.5fr),
    align: (left, left, left),
    table.header([*Назва поля*], [*Тып дадзеных*], [*Апісанне*]),
    
    [`flightNumber`], [`char[10]`], [Нумар, напрыклад "B2-737"],
    [`airline`], [`char[50]`], [Авіякампанія],
    [`city`], [`char[50]`], [Куды ляціць або адкуль прылятае],
    [`airplaneModel`], [`char[30]`], [Мадэль самалёта],
    [`type`], [`FlightType`], [Прылёт або вылет],
    [`scheduleTime`], [`DateTime`], [Час па плане],
    [`actualTime`], [`DateTime`], [Рэальны час (важна пры затрымцы)],
    [`status`], [`FlightStatus`], [Бягучы стан рэйса],
    [`terminal`], [`char`], [Літара тэрмінала (A, B, C...)],
    [`gate`], [`int`], [Нумар гейта для пасадкі],
  ),
  caption: [Структура Flight (Апісанне аднаго рэйса)]
)

// ==========================================
// Табліца 3: AirportSystem
// ==========================================
#figure(
  table(
    columns: (1fr, 1fr, 2fr),
    align: (left, left, left),
    table.header([*Назва поля*], [*Тып дадзеных*], [*Апісанне*]),
    
    [`flights`], [`Flight*`], [Указальнік на масіў у памяці],
    [`count`], [`int`], [Колькі рэйсаў рэальна запісана зараз],
    [`capacity`], [`int`], [На колькі месцаў выдзелена памяць],
  ),
  caption: [Структура AirportSystem (База дадзеных майго аэрапорта)]
)

// ==========================================
// Табліца 4: SearchFilter
// ==========================================
#figure(
  table(
    columns: (1.5fr, 1fr, 2.5fr),
    align: (left, left, left),
    table.header([*Назва поля*], [*Тып дадзеных*], [*Апісанне*]),
    
    [`useTypeFilter`], [`Boolean`], [Ці шукаю па канкрэтным напрамку],
    [`targetType`], [`FlightType`], [Сам напрамак (прылёт/вылет)],
    [`useCityFilter`], [`Boolean`], [Ці шукаю па горадзе],
    [`targetCity`], [`char[50]`], [Назва горада для пошуку],
    [`useStatusFilter`], [`Boolean`], [Ці шукаю па статусе],
    [`targetStatus`], [`FlightStatus`], [Сам статус (напрыклад, затрымліваюцца)],
    [`useTimeFilter`], [`Boolean`], [Ці шукаю па часе],
    [`startTime`], [`DateTime`], [Шукаю рэйсы толькі пасля гэтага часу],
  ),
  caption: [Структура SearchFilter (Параметры для пошуку)]
)

// ==========================================
// Табліца 5: User
// ==========================================
#figure(
  table(
    columns: (1fr, 1fr, 2fr),
    align: (left, left, left),
    table.header([*Назва поля*], [*Тып дадзеных*], [*Апісанне*]),
    
    [`username`], [`char[30]`], [Логін карыстальніка],
    [`password`], [`char[30]`], [Пароль (захоўваецца простым хэшэм)],
    [`role`], [`UserRole`], [Узровень доступу],
  ),
  caption: [Структура User (Дадзеныя карыстальніка для аўтарызацыі)]
)

// ==========================================
// Дадаткова: Табліцы для ENUM
// ==========================================

#figure(
  table(
    columns: (1.5fr, 1fr, 2fr),
    align: (left, center, left),
    table.header([*Канстанта*], [*Лікавае значэнне*], [*Апісанне*]),
    
    [`ON_TIME`], [0], [Па раскладзе],
    [`DELAYED`], [1], [Спазняецца],
    [`BOARDING`], [2], [Пасадка (калі гэта вылет)],
    [`DEPARTED`], [3], [Ужо вылецеў],
    [`LANDED`], [4], [Ужо прызямліўся],
    [`CANCELED`], [5], [Адменены],
  ),
  caption: [Пералік FlightStatus (Магчымыя станы рэйса)]
)

// Табліца з аб'яднаннем ячэек (rowspan)
#figure(
  table(
    columns: (1fr, 1.5fr, 2fr),
    align: (left, left, left),
    table.header([*Тып enum*], [*Канстанта*], [*Апісанне*]),
    
    table.cell(rowspan: 2)[`UserRole`], [`ROLE_PASSENGER`], [Можа толькі глядзець табло і шукаць],
    [`ROLE_ADMIN`], [Можа дадаваць, рэдагаваць і выдаляць],
    
    table.cell(rowspan: 2)[`FlightType`], [`ARRIVAL`], [Прылёт],
    [`DEPARTURE`], [Вылет],
  ),
  caption: [Пералікі UserRole (Ролі) і FlightType (Напрамкі)]
)