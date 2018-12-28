

RB - INSERT - FIXUP(T, z)
while color[p[z]] = RED                                                  // 若“当前节点(z)的父节点是红色”，则进行以下处理。
do if p[z] = left[p[p[z]]]                                           // 若“z的父节点”是“z的祖父节点的左孩子”，则进行以下处理。
then y ← right[p[p[z]]]                                        // 将y设置为“z的叔叔节点(z的祖父节点的右孩子)”
if color[y] = RED                                         // Case 1条件：叔叔是红色
then color[p[z]] ← BLACK                    ▹ Case 1   //  (01) 将“父节点”设为黑色。
color[y] ← BLACK                       ▹ Case 1   //  (02) 将“叔叔节点”设为黑色。
color[p[p[z]]] ← RED                   ▹ Case 1   //  (03) 将“祖父节点”设为“红色”。
z ← p[p[z]]                            ▹ Case 1   //  (04) 将“祖父节点”设为“当前节点”(红色节点)
else if z = right[p[z]]                                // Case 2条件：叔叔是黑色，且当前节点是右孩子
then z ← p[z]                       ▹ Case 2   //  (01) 将“父节点”作为“新的当前节点”。
LEFT - ROTATE(T, z)              ▹ Case 2   //  (02) 以“新的当前节点”为支点进行左旋。
color[p[z]] ← BLACK                 ▹ Case 3   // Case 3条件：叔叔是黑色，且当前节点是左孩子。(01) 将“父节点”设为“黑色”。
color[p[p[z]]] ← RED                ▹ Case 3   //  (02) 将“祖父节点”设为“红色”。
RIGHT - ROTATE(T, p[p[z]])            ▹ Case 3   //  (03) 以“祖父节点”为支点进行右旋。
else (same as then clause with "right" and "left" exchanged)      // 若“z的父节点”是“z的祖父节点的右孩子”，将上面的操作中“right”和“left”交换位置，然后依次执行。
color[root[T]] ← BLACK


FIXUP的伪代码进行说明
RB - DELETE - FIXUP(T, x)
while x ≠ root[T] and color[x] = BLACK
do if x = left[p[x]]
then w ← right[p[x]]                                             // 若 “x”是“它父节点的左孩子”，则设置 “w”为“x的叔叔”(即x为它父节点的右孩子)                                          
if color[w] = RED                                           // Case 1: x是“黑+黑”节点，x的兄弟节点是红色。(此时x的父节点和x的兄弟节点的子节点都是黑节点)。
then color[w] ← BLACK                        ▹  Case 1   //   (01) 将x的兄弟节点设为“黑色”。
color[p[x]] ← RED                       ▹  Case 1   //   (02) 将x的父节点设为“红色”。
LEFT - ROTATE(T, p[x])                    ▹  Case 1   //   (03) 对x的父节点进行左旋。
w ← right[p[x]]                         ▹  Case 1   //   (04) 左旋后，重新设置x的兄弟节点。
if color[left[w]] = BLACK and color[right[w]] = BLACK       // Case 2: x是“黑+黑”节点，x的兄弟节点是黑色，x的兄弟节点的两个孩子都是黑色。
then color[w] ← RED                          ▹  Case 2   //   (01) 将x的兄弟节点设为“红色”。
x ←  p[x]                               ▹  Case 2   //   (02) 设置“x的父节点”为“新的x节点”。
else if color[right[w]] = BLACK                          // Case 3: x是“黑+黑”节点，x的兄弟节点是黑色；x的兄弟节点的左孩子是红色，右孩子是黑色的。
then color[left[w]] ← BLACK          ▹  Case 3   //   (01) 将x兄弟节点的左孩子设为“黑色”。
color[w] ← RED                  ▹  Case 3   //   (02) 将x兄弟节点设为“红色”。
RIGHT - ROTATE(T, w)              ▹  Case 3   //   (03) 对x的兄弟节点进行右旋。
w ← right[p[x]]                 ▹  Case 3   //   (04) 右旋后，重新设置x的兄弟节点。
color[w] ← color[p[x]]                 ▹  Case 4   // Case 4: x是“黑+黑”节点，x的兄弟节点是黑色；x的兄弟节点的右孩子是红色的。(01) 将x父节点颜色 赋值给 x的兄弟节点。
color[p[x]] ← BLACK                    ▹  Case 4   //   (02) 将x父节点设为“黑色”。
color[right[w]] ← BLACK                ▹  Case 4   //   (03) 将x兄弟节点的右子节设为“黑色”。
LEFT - ROTATE(T, p[x])                   ▹  Case 4   //   (04) 对x的父节点进行左旋。
x ← root[T]                            ▹  Case 4   //   (05) 设置“x”为“根节点”。
else (same as then clause with "right" and "left" exchanged)        // 若 “x”是“它父节点的右孩子”，将上面的操作中“right”和“left”交换位置，然后依次执行。
color[x] ← BLACK