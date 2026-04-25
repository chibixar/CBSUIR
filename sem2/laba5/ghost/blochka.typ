#import "@preview/fletcher:0.4.4" as fletcher: diagram, node, edge

// Налады старонкі і шрыфта
#set page(width: auto, height: auto, margin: 20pt)
#set text(font: "Arial", size: 12pt)

// Базавыя памеры па ГОСТ
#let w = 160pt
#let h = 80pt
#let r = w / 8 // Закругленне роўна 20pt

// Карыстальніцкі вузел для "Наканаванага працэсу" (Падпраграмы)
#let subroutine(pos, body) = node(
  pos,
  width: w, height: h,
  stroke: 1pt + black,
  inset: 0pt,
  [
    #grid(
      columns: (15pt, 1fr, 15pt), 
      rows: 100%,
      stroke: (x, y) => if x == 1 or x == 2 { (left: 1pt + black) },
      [], align(center + horizon)[#body], []
    )
  ]
)

#diagram(
  node-stroke: 1pt + black,
  edge-stroke: 1pt + black,
  cell-size: (180pt, 100pt),

  // 1. Пачатак (вышыня ў 2 разы меншая: h/2)
  node((2,0), "Начало", shape: "rect", width: w, height: h / 2, radius: r),
  
  // 2. Блокі выкліку (вышыня h)
  subroutine((2,1), [выклік ф.\ showMenu()]),
  subroutine((2,2), [choice =\ выклік ф.\ getMenuChoice()]),
  
  // 3. Ромб (даўжыня w, вышыня h)
  node((2,3), "choice", shape: "diamond", width: w, height: h),

  // 4. Галіны switch
  subroutine((1,4), [выклік ф.\ handleCheck()]),
  node((2,4), [Вывад:\ "Goodbye!"], shape: "parallelogram", width: w, height: h),
  node((3,4), [Вывад:\ "Unknown\ option..."], shape: "parallelogram", width: w, height: h),

  // Пусты вузел-кропка для акуратнага злучэння ліній
  node((2,5), "", shape: "circle", radius: 0pt), 

  // 5. Ромб умовы (даўжыня w, вышыня h)
  node((2,6), "choice != 2", shape: "diamond", width: w, height: h),

  // 6. Канец (вышыня ў 2 разы меншая: h/2)
  node((2,7), "Конец", shape: "rect", width: w, height: h / 2, radius: r),

  // ================= Лініі з зафарбаванымі стрэлкамі =================
  edge((2,0), (2,1), "-|>"),
  edge((2,1), (2,2), "-|>"),
  edge((2,2), (2,3), "-|>"),

  edge((2,3), (1,3), (1,4), "-|>", label: "1", label-pos: 0.3, label-side: right),
  edge((2,3), (2,4), "-|>", label: "2", label-pos: 0.4),
  edge((2,3), (3,3), (3,4), "-|>", label: "інакш", label-pos: 0.3, label-side: left),

  edge((1,4), (1,5), (2,5), "-|>"),
  edge((2,4), (2,5), "-|>"),
  edge((3,4), (3,5), (2,5), "-|>"),

  edge((2,5), (2,6), "-|>"),

  // Стрэлка вяртання do-while (заменена bottom на left)
  edge((2,6), (0,6), (0,0.5), (2,0.5), (2,1), "-|>", label: "да", label-pos: 0.08, label-side: left),
  
  edge((2,6), (2,7), "-|>", label: "нет", label-pos: 0.3, label-side: right),
)