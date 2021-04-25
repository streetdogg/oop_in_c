/**
 * MIT License
 *
 * Copyright (c) 2021 Piyush Itankar <pitankar@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct to have data and function pointers
struct class {
    // Attributes and Data
    int data;
    void *dynamic_data;
    int dynamic_data_size;

    // constructor and destructor
    void (* constructor)(struct class *this, int data_size);
    void (* destructor)(struct class *this);

    // Methods/Member functions
    int  (* get_data_attribute)(struct class *this);
    void (* set_dynamic_data_method)(struct class *this, char* name);
    void (* get_dynamic_data_method)(struct class *this);
};


// Functions to be used as part of the object
int get_attribute(struct class *this) {
    return this->data;
}

void set_dynamic_data(struct class *this, char* name) {
    strcpy(this->dynamic_data, name);
}

void get_dynamic_data(struct class *this) {
    printf("%s\n", (char *)this->dynamic_data);
}

void class_exit(struct class *this) {
    free(this->dynamic_data);
}

// Function that would serve as constructor
void class_init(struct class *this, int data_size) {
    // Set some initial value
    this->data = 42;

    // Allocate memory for the dynamic data
    this->dynamic_data = malloc(data_size);

    // Assign all the functions to the pointers
    this->get_data_attribute = get_attribute;
    this->set_dynamic_data_method = set_dynamic_data;
    this->get_dynamic_data_method = get_dynamic_data;

    // Assign the function that will serve as destructor
    this->destructor = class_exit;
}

// Example usage
void main() {
    struct class object;

    // Just assign the constructor
    object.constructor = class_init;

    // Constructor is ready to use, 7 == sizeof("piyush")
    object.constructor(&object, 7);

    // Call member functions
    object.set_dynamic_data_method(&object, "piyush");
    object.get_dynamic_data_method(&object);
    printf("Attribute Vale: %d\n", object.get_data_attribute(&object));

    // Call destructor
    object.destructor(&object);
}