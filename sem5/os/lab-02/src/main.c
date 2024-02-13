#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define PAGE_DEFAULT_SIZE 1024 // используемую как размер для массивов страниц и таблиц страниц.

struct page {
    uint32_t frames[PAGE_DEFAULT_SIZE]; // представляющую страницу памяти, содержащую массив frames
};
// используется для представления записи в каталоге страниц
struct PDE {// труктура PDE используется для управления свойствами отдельных страниц в памяти, как часть механизма виртуальной памяти в операционных системах.
    uint32_t P : 1;
    uint32_t RW : 1;
    uint32_t US : 1;
    uint32_t PWT : 1;
    uint32_t PCD : 1;
    uint32_t A : 1;
    uint32_t D : 1;
    uint32_t PS : 1;
    uint32_t G : 1;
    uint32_t reserved : 3;
    uint32_t address : 20;
} __attribute__((packed));// гарантирует, что структура не будет иметь дополнительного выравнивания в памяти.

// Структура PTE представляет собой запись в таблице страниц. 
struct PTE { // Структура PTE используется для управления свойствами отдельных страниц в памяти в контексте механизма виртуальной памяти операционных систем.
    uint32_t P : 1;
    uint32_t RW : 1;
    uint32_t US : 1;
    uint32_t PWT : 1;
    uint32_t PCD : 1;
    uint32_t A : 1;
    uint32_t D : 1;
    uint32_t PAT : 1;
    uint32_t G : 1;
    uint32_t reserved : 3;
    uint32_t address : 20;
} __attribute__((packed));

struct PDE page_dir[PAGE_DEFAULT_SIZE] __attribute__((aligned(PAGE_DEFAULT_SIZE * 4)));// Объявление Массива Каталога Страниц
struct PTE page_tab[PAGE_DEFAULT_SIZE][PAGE_DEFAULT_SIZE] __attribute__((aligned(PAGE_DEFAULT_SIZE * 4)));//  Объявление Массива Таблиц Страниц
// представляет собой структуру, содержащую данные одной страницы
struct page page_0;// Объявление Структуры Страницы
// В контексте систем с виртуальной памятью, как правило, cr3 используется процессором для поиска 
// записей каталога страниц при переводе виртуальных адресов в физические.
uint32_t cr3; // используется для хранения физического адреса каталога страниц (page_dir)

// Функция print_mmu эффективно демонстрирует, как виртуальные адреса отображаются на
// физические адреса в системе управления виртуальной памятью, показывая соответствие между 
// записями в таблицах страниц и их физическими адресами.
void print_mmu(uint32_t page_tab_count, uint32_t page_count) {
    printf("table addr\n");
    for (uint32_t i = 0; i < page_tab_count; ++i) {
        printf("0x%x\n", (uint32_t)((page_dir[i]).address));
        printf("physical\tvirtual\n");
        for (uint32_t j = 0; j < PAGE_DEFAULT_SIZE; ++j) {
            printf("%p\t\t", (void *)(uintptr_t)((page_tab[i][j]).address << 12));
            printf("%p\t\t", (void *)(uintptr_t)(((i << 10) | j) << 12));
        }
    }
}

int main(int argc, char **argv) {
    cr3 = ((uintptr_t)page_dir >> 12) << 12;// физического адреса каталога страниц    
    uint32_t bin_size = 4096 * 16;// общий размер памяти

    uint32_t page_count = bin_size / 4096;
    if ((bin_size % 4096) > 0) page_count++;
    uint32_t page_tab_count = page_count / 1024;
    if ((page_count % 1024) > 0) page_tab_count++; // вычисляется количество таблиц страниц 

    for (uint16_t i = 0; i < page_tab_count; i++) {// Начинается цикл, который проходит по каждой таблице страниц
        page_dir[i] = (struct PDE) {
            .P = 1, .RW = 1, .US = 1, .PWT = 1, .PCD = 1, .A = 0, .D = 1,
            .PS = 1, .address = (uintptr_t)(&page_tab[i]) >> 12};
        for (uint32_t j = 0; j < PAGE_DEFAULT_SIZE; j++) {// Внутренний цикл, который проходит по каждой записи в текущей таблице страниц.
            page_tab[i][j] = (struct PTE){ .D = 0, .A = 0, .PAT = 0, .PCD = 0,
            .G = 1, .P = 1, .RW = 1, .US = 1, .PWT = 1,
            .address = ((uintptr_t)(&page_0) + j * 4096) >> 12};
        }
    }
    
    printf("memsize = %d, ", bin_size);
    printf("pgdiraddr = %p, ", (void *)page_dir);
    printf("pgtabcnt = %d, ", page_tab_count);
    printf("pgcnt = %d\n\n", page_count);
    printf("MMU table\n");
    print_mmu(page_tab_count, page_count);
}
