#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contact {
    char name[50];
    char phone[15];
    char photo[100];
    struct Contact* left;
    struct Contact* right;
} Contact;

Contact* root = NULL;

Contact* createContact(const char* name, const char* phone, const char* photo) {
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    if (newContact == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    strcpy(newContact->photo, photo);
    newContact->left = NULL;
    newContact->right = NULL;
    return newContact;
}

Contact* insertContact(Contact* node, Contact* newContact) {
    if (node == NULL) {
        return newContact;
    }
    int cmp = strcmp(newContact->name, node->name);
    if (cmp < 0) {
        node->left = insertContact(node->left, newContact);
    } else if (cmp > 0) {
        node->right = insertContact(node->right, newContact);
    }
    return node;
}

void addContact() {
    char name[50];
    char phone[15];
    char photo[100];

    printf("Enter the following information for the new contact:\n");
    printf("Name: ");
    scanf("%s", name);
    printf("Phone: ");
    scanf("%s", phone);
    printf("Image Path: ");
    scanf("%s", photo);

    Contact* newContact = createContact(name, phone, photo);
    root = insertContact(root, newContact);
    printf("Contact added successfully.\n");
}

Contact* findMinContact(Contact* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

Contact* deleteContact(Contact* node, const char* name) {
    if (node == NULL) {
        return node;
    }
    int cmp = strcmp(name, node->name);
    if (cmp < 0) {
        node->left = deleteContact(node->left, name);
    } else if (cmp > 0) {
        node->right = deleteContact(node->right, name);
    } else {
        if (node->left == NULL) {
            Contact* temp = node->right;
            free(node);
            return temp;
        } else if (node->right == NULL) {
            Contact* temp = node->left;
            free(node);
            return temp;
        }
        Contact* temp = findMinContact(node->right);
        strcpy(node->name, temp->name);
        strcpy(node->phone, temp->phone);
        strcpy(node->photo, temp->photo);
        node->right = deleteContact(node->right, temp->name);
    }
    return node;
}

void removeContact() {
    char name[50];
    printf("Enter the name of the contact you want to delete: ");
    scanf("%s", name);
    root = deleteContact(root, name);
    printf("Contact deleted successfully.\n");
}

Contact* findContact(Contact* node, const char* name) {
    if (node == NULL) {
        return NULL;
    }
    int cmp = strcmp(name, node->name);
    if (cmp == 0) {
        return node;
    } else if (cmp < 0) {
        return findContact(node->left, name);
    } else {
        return findContact(node->right, name);
    }
}

void searchContact() {
    char name[50];
    printf("Enter the name of the contact you want to search for: ");
    scanf("%s", name);
    Contact* contact = findContact(root, name);
    if (contact) {
        printf("Contact found:\n");
        printf("Name: %s\n", contact->name);
        printf("Phone: %s\n", contact->phone);
        printf("Image Path: %s\n", contact->photo);
    } else {
        printf("Contact not found.\n");
    }
}

void updateContact(Contact* node, const char* name, const char* phone, const char* photo) {
    strcpy(node->phone, phone);
    strcpy(node->photo, photo);
}

void modifyContact() {
    char name[50];
    printf("Enter the name of the contact you want to update: ");
    scanf("%s", name);
    Contact* contact = findContact(root, name);
    if (contact) {
        char phone[15];
        char photo[100];
        printf("Enter the updated information for the contact:\n");
        printf("Phone: ");
        scanf("%s", phone);
        printf("Image Path: ");
        scanf("%s", photo);
        updateContact(contact,name, phone, photo);
        printf("Contact updated successfully.\n");
    } else {
        printf("Contact not found.\n");
    }
}

void displayContacts(Contact* node) {
    if (node != NULL) {
        displayContacts(node->left);
        printf("Name: %s\n", node->name);
        printf("Phone: %s\n", node->phone);
        printf("Image Path: %s\n", node->photo);
        printf("\n");
        displayContacts(node->right);
    }
}

void listContacts() {
    if (root == NULL) {
        printf("No contacts in the list.\n");
    } else {
        printf("List of all contacts:\n");
        displayContacts(root);
    }
}

void freeContacts(Contact* node) {
    if (node != NULL) {
        freeContacts(node->left);
        freeContacts(node->right);
        free(node);
    }
}

int main() {
    int choice;

    while (1) {
        printf("Contact Management System\n");
        printf("1. Add Contact\n");
        printf("2. Delete Contact\n");
        printf("3. Search Contact\n");
        printf("4. Update Contact\n");
        printf("5. List Contacts\n");
        printf("6. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                removeContact();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                modifyContact();
                break;
            case 5:
                listContacts();
                break;
            case 6:
                freeContacts(root);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

