#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { RED, BLACK } color_t;

typedef struct Node {
    int key;
    color_t color;
    struct Node* left, * right, * parent;
    /* layout info for visualization */
    int x;   // column position
    int y;   // depth (level)
} Node;

/* Global sentinel and root */
Node* NIL;
Node* ROOT;

/* ----- utility/new/init ----- */
Node* new_node(int key) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) { fprintf(stderr, "malloc failed\n"); exit(1); }
    n->key = key;
    n->color = RED;
    n->left = n->right = n->parent = NIL;
    n->x = n->y = 0;
    return n;
}

void tree_init(void) {
    NIL = (Node*)malloc(sizeof(Node));
    if (!NIL) { fprintf(stderr, "malloc failed\n"); exit(1); }
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NIL;
    NIL->x = NIL->y = 0;
    ROOT = NIL;
}

/* ----- rotations ----- */
void left_rotate(Node** Troot, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) *Troot = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void right_rotate(Node** Troot, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NIL) x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NIL) *Troot = x;
    else if (y == y->parent->right) y->parent->right = x;
    else y->parent->left = x;
    x->right = y;
    y->parent = x;
}

/* ----- insert & fixup ----- */
void rb_insert_fixup(Node** Troot, Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(Troot, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(Troot, z->parent->parent);
            }
        }
        else {
            Node* y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(Troot, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(Troot, z->parent->parent);
            }
        }
    }
    (*Troot)->color = BLACK;
}

void rb_insert(Node** Troot, Node* z) {
    Node* y = NIL;
    Node* x = *Troot;
    while (x != NIL) {
        y = x;
        if (z->key < x->key) x = x->left; else x = x->right;
    }
    z->parent = y;
    if (y == NIL) *Troot = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;
    z->left = z->right = NIL;
    z->color = RED;
    rb_insert_fixup(Troot, z);
}

/* ----- transplant / minimum ----- */
void rb_transplant(Node** Troot, Node* u, Node* v) {
    if (u->parent == NIL) *Troot = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

Node* tree_minimum(Node* x) {
    while (x->left != NIL) x = x->left;
    return x;
}

/* ----- delete & fixup ----- */
void rb_delete_fixup(Node** Troot, Node* x) {
    while (x != *Troot && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(Troot, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(Troot, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(Troot, x->parent);
                x = *Troot;
            }
        }
        else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(Troot, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(Troot, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(Troot, x->parent);
                x = *Troot;
            }
        }
    }
    x->color = BLACK;
}

void rb_delete(Node** Troot, Node* z) {
    Node* y = z;
    color_t y_original_color = y->color;
    Node* x;
    if (z->left == NIL) {
        x = z->right;
        rb_transplant(Troot, z, z->right);
    }
    else if (z->right == NIL) {
        x = z->left;
        rb_transplant(Troot, z, z->left);
    }
    else {
        y = tree_minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        }
        else {
            rb_transplant(Troot, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rb_transplant(Troot, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (y_original_color == BLACK) rb_delete_fixup(Troot, x);
}

/* ----- search helper ----- */
Node* tree_search(Node* root, int key) {
    Node* x = root;
    while (x != NIL && key != x->key) {
        if (key < x->key) x = x->left; else x = x->right;
    }
    return x;
}

/* ------------------ Visualization ------------------
   Layout approach:
   - Inorder traversal assigns increasing x positions (counter).
   - y = depth.
   - Canvas sized from node count and depth.
   - Draw node labels "key(R/B)" at (row=y*3, col=x).
   - Draw connectors '/' '\' and draw "NIL" where child == NIL.
----------------------------------------------------*/

typedef struct {
    int cols;
    int rows;
    char** buf;
} Canvas;

Canvas make_canvas(int rows, int cols) {
    Canvas c;
    c.rows = rows;
    c.cols = cols;
    c.buf = (char**)malloc(rows * sizeof(char*));
    for (int r = 0; r < rows; ++r) {
        c.buf[r] = (char*)malloc(cols + 1);
        for (int j = 0; j < cols; ++j) c.buf[r][j] = ' ';
        c.buf[r][cols] = '\0';
    }
    return c;
}

void free_canvas(Canvas* c) {
    for (int r = 0; r < c->rows; ++r) free(c->buf[r]);
    free(c->buf);
}

void print_canvas(Canvas* c) {
    for (int r = 0; r < c->rows; ++r) {
        printf("%s\n", c->buf[r]);
    }
}

/* layout assignment (inorder index -> x) */
int layout_counter;
int max_depth;

void assign_positions(Node* n, int depth, int spacing) {
    if (n == NIL) return;
    if (depth > max_depth) max_depth = depth;
    assign_positions(n->left, depth + 1, spacing);
    layout_counter++;
    n->x = layout_counter * spacing;
    n->y = depth;
    assign_positions(n->right, depth + 1, spacing);
}

/* put string into canvas with boundary check */
void canvas_put(Canvas* c, int row, int col, const char* s) {
    if (row < 0 || row >= c->rows) return;
    int len = (int)strlen(s);
    for (int i = 0; i < len; ++i) {
        int cc = col + i;
        if (cc >= 0 && cc < c->cols) c->buf[row][cc] = s[i];
    }
}

/* draw connectors between parent and child */
void draw_connection(Canvas* c, int prow, int pcol, int crow, int ccol) {
    if (prow == crow) return;
    int dr = crow - prow;
    int dc = ccol - pcol;
    // simple diagonal-ish: place '/' or '\' at one row below parent and one col towards child
    if (dc < 0) {
        // left child: put '/' a cell below-left and possibly vertical '|'
        int rr = prow + 1;
        int cc = pcol - 1;
        if (rr >= 0 && rr < c->rows && cc >= 0 && cc < c->cols) c->buf[rr][cc] = '/';
    }
    else if (dc > 0) {
        int rr = prow + 1;
        int cc = pcol + 1;
        if (rr >= 0 && rr < c->rows && cc >= 0 && cc < c->cols) c->buf[rr][cc] = '\\';
    }
}

/* draw nil marker at given position */
void draw_nil(Canvas* c, int row, int col) {
    canvas_put(c, row, col, "NIL");
}

/* recursive drawing */
void draw_tree(Canvas* c, Node* n) {
    if (n == NIL) return;
    int row = n->y * 3;
    int col = n->x;
    char label[32];
    sprintf(label, "%d(%c)", n->key, (n->color == RED ? 'R' : 'B'));
    canvas_put(c, row, col, label);

    // left child
    if (n->left != NIL) {
        int crow = n->left->y * 3;
        int ccol = n->left->x;
        draw_connection(c, row, col, crow, ccol);
        draw_tree(c, n->left);
    }
    else {
        // draw NIL under left
        int nilrow = row + 3;
        int nilcol = col - 4; // shift left
        draw_nil(c, nilrow, nilcol);
    }

    // right child
    if (n->right != NIL) {
        int crow = n->right->y * 3;
        int ccol = n->right->x;
        draw_connection(c, row, col, crow, ccol);
        draw_tree(c, n->right);
    }
    else {
        // draw NIL under right
        int nilrow = row + 3;
        int len = (int)strlen(label);
        int nilcol = col + len + 1; // shift right
        draw_nil(c, nilrow, nilcol);
    }
}

/* top-level print */
void print_tree(Node* root) {
    if (root == NIL) { printf("(empty tree)\n"); return; }

    layout_counter = 0;
    max_depth = 0;
    int spacing = 7; // column spacing between nodes (tune if needed)
    assign_positions(root, 0, spacing);
    int cols = (layout_counter + 3) * spacing + 20;
    int rows = (max_depth + 2) * 3 + 2;
    Canvas c = make_canvas(rows, cols);

    draw_tree(&c, root);
    print_canvas(&c);
    free_canvas(&c);
}

/* ---------------------- main ---------------------- */
int main(void) {
    tree_init();

    int keys[] = { 13, 8, 17, 1, 11, 15, 25, 6, 22, 27 };
    int n = sizeof(keys) / sizeof(keys[0]);

    printf("Inserting keys:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d ", keys[i]);
        Node* z = new_node(keys[i]);
        rb_insert(&ROOT, z);
    }
    printf("\n\nTree after insertions:\n\n");
    print_tree(ROOT);

    /* Example: delete a couple of keys and print */
    int dels[] = { 8, 17 };
    int dn = sizeof(dels) / sizeof(dels[0]);
    for (int i = 0; i < dn; ++i) {
        int k = dels[i];
        Node* t = tree_search(ROOT, k);
        if (t == NIL) printf("\nKey %d not found\n", k);
        else {
            rb_delete(&ROOT, t);
            printf("\nTree after deleting %d:\n\n", k);
            print_tree(ROOT);
        }
    }

    return 0;
}
