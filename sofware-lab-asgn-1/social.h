// structures and unions

// Common structure representing shared attributes among entities
// It will be used in all 4 structures
struct common {
  int id;            // Unique identifier
  char name[100];    // Name of the node
  char date[100];    // Entry date of node
  char content[100]; // Content of node
};

// Structure representing an individual with common attributes and links
struct individual {
  struct common cmn;       // Common attributes
  char birthDate[100];     // Birthdate of individual
  struct individual *next; // Pointer to the next individual
  int moforg[100];         // IDs of organizations the individual is part of
  int nofmoforg;           // Number of organizations the individual is part of
  int mofgrp[100];         // IDs of groups the individual is part of
  int nofmofgrp;           // Number of groups the individual is part of
  int mofbsncus[100];      // IDs of businesses where individual is a customer
  int nofmofbsncus;        // Number of businesses where individual is a customer
  int mofbsncown[100];     // IDs of businesses where individual is an owner
  int nofmofbsnown;        // Number of businesses where individual is an owner
};

// Structure representing a place with X and Y coordinates
struct place {
  int x; // X coordinate
  int y; // Y coordinate
};

// Structure representing a business with common attributes, location, and links
struct business {
  struct common cmn;           // Common attributes
  struct place location;       // Location coordinates
  struct indlist *bsntoindcus; // Head of linked list of customers linked to the business
  struct indlist *topcus;      // Tail of linked list of customer nodes
  struct indlist *bsntoindown; // Head of linked list of owners linked to the business
  struct indlist *topown;      // Tail of linked list of owner nodes
  int nofcus;                  // Number of customers linked to the business
  int nofown;                  // Number of owners linked to the business
  int mofgrp[100];             // IDs of groups the business is part of
  int nofmofgrp;               // Number of groups the business is part of
  struct business *next;       // Pointer to the next business
};

// Structure representing a node in the individual linked list
struct indlist {
  struct individual *ind; // Pointer to an individual node
  struct indlist *next;   // Pointer to the next element in list
};

// Structure representing a node in the business linked list
struct bsnlist {
  struct business *bsn; // Pointer to a business node
  struct bsnlist *next; // Pointer to the next element in list
};

// Structure representing an organization with common attributes and links
struct organisation {
  struct common cmn;         // Common attributes
  struct place location;     // Location coordinates
  struct indlist *orgtoind;  // Head of linked list of of individuals linked to the organization
  struct indlist *top;       // Tail of linked list of individual nodes
  struct organisation *next; // Pointer to the next organization
  int nofm;                  // Number of individuals linked to the organization
};

// Structure representing a group with common attributes and links
struct group {
  struct common cmn;        // Common attributes
  struct indlist *grptoind; // Head of linked list of individuals linked to the group
  struct indlist *indtop;   // Tail of linked list of individual nodes
  struct bsnlist *grptobsn; // Head of linked list of of businesses linked to the group
  struct bsnlist *bsntop;   // Tail of linked list of business nodes
  struct group *next;       // Pointer to the next group
  int nofim;                // Number of individuals linked to the group
  int nofbm;                // Number of businesses linked to the group
};

// metadata contains all useful information about type and presence for easier access of id to pointer
// Union is used since only one of the 4 types is used for one metadata
struct metadata {
  int present; // Present flag
  int type;    // Type identifier (1, 2, 3, 4) as per masterinterface
  union {
    struct individual *ind; // Pointer to one of 4 types of nodes
    struct group *grp;
    struct business *bsn;
    struct organisation *org;
  };
};

// typedefs for structures
typedef struct individual individual;
typedef struct group group;
typedef struct business business;
typedef struct organisation organisation;
typedef struct indlist indlist;
typedef struct bsnlist bsnlist;
typedef struct metadata metadata;
typedef struct group group;
typedef struct business business;
typedef struct organisation organisation;

// Function declarations

// Function to create nodes and initialize data
void create();

// Function to add a new business node to business nodes list and initialize data
void createBusiness();

// Function to add a new group node to group nodes list and initialize data
void createGroup();

// Function to add a new organisation node to organisation nodes list and initialize data
void createOrganisation();

// Function to add a new individual node to individual nodes list and initialize data
void craeteIndividual();

// Function to add links for a given organization
void addLinksForOrg(organisation *org);

// Function to add links for a given business
void addLinksForBusiness(business *bsn);

// Function to add links for a given group
void addLinksForGroup(group *grp);

// Function to delete a node with given id
void delete(int id);

// Function to delete traces and footprints for a group
void deleteTracesOfGroup(int givenId);

// Function to delete traces and footprints for a business
void deleteTracesOfBusiness(int givenId);

// Function to delete traces and footprints for an organization
void deleteTracesOfOrganisation(int givenId);

// Function to delete traces and footprints for an individual
void deleteTracesOfIndividual(int givenId);

// Function to find the id of previous node in their list
int findPrev(int givenId);

// Function to find the id of next node in their list
int findNext(int givenId);

// Function to tell if given id possible by limits
int isIdPossible(int givenId);

// Function to tell if given id present in the system
int isIdPresent(int givenId);

// Function to search for node by name
int searchByName();

// Function to search for nodes by type
int searchByType();

// Function to search for node by birthday
int searchByBirthDay();

// Function to print 1-hop linked nodes for a given node
void printLinkedNodes();

// Function to create a post by a node
void createContent();

// Function to get post by a given node
void printContentByNode(int id);

// Function to display posts by linked individual nodes for a given individual node
void printContentByLinkedNodes();

// Function for the main interface
int masterInterface();
