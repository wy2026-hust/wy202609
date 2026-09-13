#include <stdio.h>
#include <string.h>

// 商品结构体
typedef struct {
    char name[20];
    char code[10];
    double price;
} Product;

// 商品列表
Product products[] = {
    {"Cola", "001", 3.50},
    {"Lollipop", "002", 0.50},
    {"Noodles", "003", 6.00}
};
// 商品总数
const int product_cnt = sizeof(products) / sizeof(Product);

// 根据条码查找商品，找到返回下标，找不到返回-1
int find_product(const char *code) {
    for (int i = 0; i < product_cnt; i++) {
        if (strcmp(products[i].code, code) == 0) {
            return i;
        }
    }
    return -1;
}

// 打印所有商品（prices命令）
void print_all_goods(void) {
    printf("Item      No. Pri.\n");
    printf("----------------\n");
    for (int i = 0; i < product_cnt; i++) {
        printf("%-9s %s %.2f\n", products[i].name, products[i].code, products[i].price);
    }
}

int main(void) {
    char input_buf[256];
    while (1) {
        printf("> ");
        // 读取一行输入
        fgets(input_buf, sizeof(input_buf), stdin);
        // 去掉末尾换行符
        input_buf[strcspn(input_buf, "\n")] = '\0';

        // 判断退出命令
        if (strcmp(input_buf, "exit") == 0 || strcmp(input_buf, "quit") == 0) {
            break;
        }
        // prices命令
        if (strcmp(input_buf, "prices") == 0) {
            print_all_goods();
            continue;
        }

        // 分割输入，支持一次性输入多个条码（如 > 001 003）
        char *token = strtok(input_buf, " ");
        int has_error = 0;
        while (token != NULL) {
            int idx = find_product(token);
            if (idx >= 0) {
                printf("%s %.2f\n", products[idx].name, products[idx].price);
            } else {
                printf("ERROR: code not found\n");
                has_error = 1;
            }
            token = strtok(NULL, " ");
        }
    }
    return 0;
}
