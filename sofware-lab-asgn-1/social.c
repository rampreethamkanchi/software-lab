#include "social.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// global variables
int id = 0;                                 // index will be in order of creation of node
int nofi = 0, nofo = 0, nofg = 0, nofb = 0; // number of nodes of each type

// maintaining 4 main lists for each type with head and tail
individual *individualListHead;
individual *individualListTail;
group *groupListHead;
group *groupListTail;
business *businessListHead;
business *busninessListTail;
organisation *organisationListHead;
organisation *organisationListTail;

metadata metaArr[100]; // metadata metaArray for easier access of type and to check presence.

// implimentations of functions

int isIdPossible(int givenId) {
  if (givenId < id)
    return 1;
  return 0;
}

int isIdPresent(int givenId) {
  if (isIdPossible(givenId)) {
    if (metaArr[givenId].present)
      return 1;
  }
  return 0;
}

void addLinksForGroup(group *grp) {
  int givenId;
  int flag;
  do {
    printf("Enter 1 to add an individual and 2 to add a business to this group, else enter 3: ");
    scanf("%d", &flag);

    if (flag == 1) {
      printf("Enter id of the individual: ");
      scanf("%d", &givenId);

      if (isIdPresent(givenId) && metaArr[givenId].type == 1) {
        // Check if the given id is a valid individual id
        indlist *node = malloc(sizeof(indlist));
        node->ind = metaArr[givenId].ind;

        // Add to the group's linked list of individual members
        if (grp->grptoind == NULL) {
          grp->grptoind = node;
          grp->indtop = grp->grptoind;
        } else {
          grp->indtop->next = node;
          grp->indtop = grp->indtop->next;
        }

        // Update individual's links to groups
        (metaArr[givenId].ind)->mofgrp[(metaArr[givenId].ind)->nofmofgrp] = (grp->cmn).id;
        ((metaArr[givenId].ind)->nofmofgrp)++;
        grp->nofim++;
      } else {
        printf("Invalid individual id.\n");
      }
    } else if (flag == 2) {
      printf("Enter id of the business: ");
      scanf("%d", &givenId);

      if (isIdPresent(givenId) && metaArr[givenId].type == 3) {
        // Check if the given id is a valid business id
        bsnlist *node = malloc(sizeof(bsnlist));
        node->bsn = metaArr[givenId].bsn;

        // Add to the group's linked list of business members
        if (grp->grptobsn == NULL) {
          grp->grptobsn = node;
          grp->bsntop = grp->grptobsn;
        } else {
          grp->bsntop->next = node;
          grp->bsntop = grp->bsntop->next;
        }

        // Update business's links to groups
        (metaArr[givenId].bsn)->mofgrp[(metaArr[givenId].bsn)->nofmofgrp] = (grp->cmn).id;
        ((metaArr[givenId].bsn)->nofmofgrp)++;
        grp->nofbm++;
      } else {
        printf("Invalid business id.\n");
      }
    }

  } while (flag != 3);
}

void addLinksForBusiness(business *bsn) {
  int givenId;
  int flag;

  do {
    printf("Enter 1 to add a customer and 2 to add an owner to this business, else enter 3: ");
    scanf("%d", &flag);

    if (flag == 1) {
      printf("Enter id of the individual customer: ");
      scanf("%d", &givenId);

      if (isIdPresent(givenId) && metaArr[givenId].type == 1) {
        // Check if the given id is a valid individual id
        indlist *node = malloc(sizeof(indlist));
        node->ind = metaArr[givenId].ind;

        // Add to the business's linked list of individual customers
        if (bsn->bsntoindcus == NULL) {
          bsn->bsntoindcus = node;
          bsn->topcus = bsn->bsntoindcus;
        } else {
          bsn->topcus->next = node;
          bsn->topcus = bsn->topcus->next;
        }

        // Update individual's links to the business as a customer
        (metaArr[givenId].ind)->mofbsncus[(metaArr[givenId].ind)->nofmofbsncus] = (bsn->cmn).id;
        ((metaArr[givenId].ind)->nofmofbsncus)++;
        bsn->nofcus++;
      } else {
        printf("Invalid individual id.\n");
      }
    } else if (flag == 2) {
      printf("Enter id of the individual owner: ");
      scanf("%d", &givenId);

      if (isIdPresent(givenId) && metaArr[givenId].type == 1) {
        // Check if the given id is a valid individual id
        indlist *node = malloc(sizeof(indlist));
        node->ind = metaArr[givenId].ind;

        // Add to the business's linked list of individual owners
        if (bsn->bsntoindown == NULL) {
          bsn->bsntoindown = node;
          bsn->topown = bsn->bsntoindown;
        } else {
          bsn->topown->next = node;
          bsn->topown = bsn->topown->next;
        }

        // Update individual's links to the business as an owner
        (metaArr[givenId].ind)->mofbsncown[(metaArr[givenId].ind)->nofmofbsnown] = (bsn->cmn).id;
        ((metaArr[givenId].ind)->nofmofbsnown)++;
        bsn->nofown++;
      } else {
        printf("Invalid individual id.\n");
      }
    }

  } while (flag != 3);
}

void addLinksForOrg(organisation *org) {
  int givenId;
  int flag;
  do {
    printf("Enter 1 if you want to add member to this organisation, else enter 2 : ");
    scanf("%d", &flag);
    if (flag == 1) {
      printf("Enter id of the individual : ");
      scanf("%d", &givenId);
      if (isIdPresent(givenId)) {
        if (metaArr[givenId].type == 1) {
          indlist *node = malloc(sizeof(indlist));
          node->ind = metaArr[givenId].ind;
          if (org->orgtoind == NULL) {
            org->orgtoind = node;
            org->top = org->orgtoind;
          } else {
            org->top->next = node;
            org->top = org->top->next;
          }
          (org->nofm)++;
          ((metaArr[givenId].ind)->moforg)[(metaArr[givenId].ind)->nofmoforg] = (org->cmn).id;
          ((metaArr[givenId].ind)->nofmoforg)++;
        } else {
          printf("cant link to it. please link only to individuals.\n");
        }
      } else {
        printf("invalid id\n");
      }
    }
  } while (flag == 1);
}
void craeteIndividual() {
  individual *ind = malloc(sizeof(individual));

  if (individualListHead == NULL) {
    // empty list
    individualListHead = ind;
    individualListTail = ind;
  } else {
    individualListTail->next = ind;
    individualListTail = individualListTail->next;
  }
  printf("Enter name : ");
  getchar();
  scanf("%[^\n]s", (ind->cmn).name);
  printf("Enter date in dd-mm-yyyy format eg: 19-07-2004 : ");
  getchar();
  scanf("%[^\n]s", (ind->cmn).date);
  getchar();
  printf("Enter birthdate in dd-mm-yyyy format eg: 19-07-2004 : ");
  scanf("%[^\n]s", ind->birthDate);
  (ind->cmn).id = id;
  (ind->cmn).content[0] = '\0';
  ind->next = NULL;
  ind->nofmoforg = 0;
  // add to metadata
  metaArr[id].present = 1;
  metaArr[id].type = 1;
  metaArr[id].ind = ind;
  id++;
  nofi++;
}
void createOrganisation() {
  organisation *ind = malloc(sizeof(organisation));
  if (organisationListHead == NULL) {
    // empty list
    organisationListHead = ind;
    organisationListTail = ind;
  } else {
    organisationListTail->next = ind;
    organisationListTail = organisationListTail->next;
  }
  getchar();
  printf("Enter name : ");
  scanf("%[^\n]s", (ind->cmn).name);
  printf("Enter date in dd-mm-yyyy format eg: 19-07-2004 : ");
  getchar();
  scanf("%[^\n]s", (ind->cmn).date);
  printf("Enter x, y of location : ");
  scanf("%d%d", &((ind->location).x), &((ind->location).y));
  ind->nofm = 0;
  (ind->cmn).id = id;
  (ind->cmn).content[0] = '\0';
  ind->next = NULL;
  ind->orgtoind = NULL;
  addLinksForOrg(ind);
  metaArr[id].present = 1;
  metaArr[id].type = 4;
  metaArr[id].org = ind;
  id++;
  nofo++;
}
void createGroup() {
  group *ind = malloc(sizeof(group));
  if (groupListHead == NULL) {
    // empty list
    groupListHead = ind;
    groupListTail = ind;
  } else {
    groupListTail->next = ind;
    groupListTail = groupListTail->next;
  }
  printf("Enter name : ");
  getchar();
  scanf("%[^\n]s", (ind->cmn).name);
  printf("Enter date in dd-mm-yyyy format eg: 19-07-2004 : ");
  getchar();
  scanf("%[^\n]s", (ind->cmn).date);
  ind->nofbm = 0;
  ind->nofim = 0;
  (ind->cmn).id = id;
  (ind->cmn).content[0] = '\0';
  ind->next = NULL;
  ind->grptobsn = NULL;
  ind->grptoind = NULL;
  addLinksForGroup(ind);
  metaArr[id].present = 1;
  metaArr[id].type = 2;
  metaArr[id].grp = ind;
  id++;
  nofg++;
}
void createBusiness() {
  business *ind = malloc(sizeof(business));
  if (businessListHead == NULL) {
    // empty list
    businessListHead = ind;
    busninessListTail = ind;
  } else {
    busninessListTail->next = ind;
    busninessListTail = busninessListTail->next;
  }
  printf("Enter name : ");
  getchar();
  scanf("%[^\n]s", (ind->cmn).name);
  printf("Enter date in dd-mm-yyyy format eg: 19-07-2004 : ");
  getchar();
  scanf("%[^\n]s", (ind->cmn).date);
  printf("Enter x, y of location : ");
  scanf("%d%d", &((ind->location).x), &((ind->location).y));
  ind->nofcus = 0;
  ind->nofown = 0;
  ind->nofmofgrp = 0;
  (ind->cmn).content[0] = '\0';
  (ind->cmn).id = id;
  ind->next = NULL;
  ind->bsntoindown = NULL;
  ind->bsntoindcus = NULL;
  addLinksForBusiness(ind);
  metaArr[id].present = 1;
  metaArr[id].type = 3;
  metaArr[id].bsn = ind;
  id++;
  nofb++;
}

void create() {
  // create, type
  printf("1 for individual, 2 for group, 3 for bussiness and 4 for organisation\n");
  int z;
  scanf("%d", &z);
  if (z == 1) {
    // individual
    craeteIndividual();
  } else if (z == 2) {
    // group
    createGroup();
    // links to individual, bussiness
  } else if (z == 3) {
    // bussiness
    createBusiness();
    // links to owners and customers
  } else if (z == 4) {
    createOrganisation();
    // links to individuals
  } else {
    printf("Enter valid option\n");
  }
};
int findNext(int givenId) {
  int type = metaArr[givenId].type;
  for (int i = givenId + 1; i < id; i++) {
    if (metaArr[i].present) {
      if (metaArr[i].type == type) {
        return i;
      }
    }
  }
  return 0;
}
int findPrev(int givenId) {
  int type = metaArr[givenId].type;
  for (int i = givenId - 1; i >= 0; i--) {
    if (metaArr[i].present) {
      if (metaArr[i].type == type) {
        return i;
      }
    }
  }
  return -1;
}
//! check for multiple oraganisations case
void deleteTracesOfIndividual(int givenId) {
  // Delete traces from organizations
  int numOrgs = (metaArr[givenId].ind)->nofmoforg;
  for (int i = 0; i < numOrgs; i++) {
    int orgId = ((metaArr[givenId].ind)->moforg)[i];
    if (orgId >= 0) {
      indlist *orgNode = (metaArr[orgId].org)->orgtoind;
      int nofMembersOrg = (metaArr[orgId].org)->nofm;
      if (orgNode != NULL) {
        // Check and delete the node
        if (((orgNode->ind)->cmn).id == givenId) {
          if (orgNode->next == NULL) {
            // Last element
            (metaArr[orgId].org)->orgtoind = NULL;
          } else {
            // Middle or first element
            (metaArr[orgId].org)->orgtoind = orgNode->next;
          }
        } else {
          // Not first node, it's middle or last
          for (int j = 0; j < nofMembersOrg - 1; j++) {
            if ((((orgNode->next)->ind)->cmn).id == givenId) {
              if (orgNode->next->next == NULL) {
                // Last element
                orgNode->next = NULL;
              } else {
                // Middle element
                orgNode->next = orgNode->next->next;
              }
              break;
            }
            orgNode = orgNode->next;
          }
        }
        // Decrease the count
        ((metaArr[orgId].org)->nofm)--;
      }
    }
  }

  // Delete traces from groups
  int numGroups = (metaArr[givenId].ind)->nofmofgrp;
  for (int i = 0; i < numGroups; i++) {
    int groupId = ((metaArr[givenId].ind)->mofgrp)[i];

    if (groupId >= 0) {
      indlist *groupNode = (metaArr[groupId].grp)->grptoind;
      int nofMembersGroup = (metaArr[groupId].grp)->nofim;
      if (groupNode != NULL) {
        // Check and delete the node
        if (((groupNode->ind)->cmn).id == givenId) {
          if (groupNode->next == NULL) {
            // Last element
            (metaArr[groupId].grp)->grptoind = NULL;
          } else {
            // Middle or first element
            (metaArr[groupId].grp)->grptoind = groupNode->next;
          }
        } else {
          // Not first node, it's middle or last
          for (int j = 0; j < nofMembersGroup - 1; j++) {
            if ((((groupNode->next)->ind)->cmn).id == givenId) {
              if (groupNode->next->next == NULL) {
                // Last element
                groupNode->next = NULL;
              } else {
                // Middle element
                groupNode->next = groupNode->next->next;
              }
              break;
            }
            groupNode = groupNode->next;
          }
        }
        // Decrease the count
        ((metaArr[groupId].grp)->nofim)--;
      }
    }
  }

  // Delete traces from businesses
  int numBusinesses = (metaArr[givenId].ind)->nofmofbsncus;
  for (int i = 0; i < numBusinesses; i++) {
    int businessId = ((metaArr[givenId].ind)->mofbsncus)[i];
    if (businessId >= 0) {
      indlist *businessNodeCus = (metaArr[businessId].bsn)->bsntoindcus;
      int nofCustomers = (metaArr[businessId].bsn)->nofcus;

      if (businessNodeCus != NULL) {
        // Check and delete the node
        if (((businessNodeCus->ind)->cmn).id == givenId) {
          if (businessNodeCus->next == NULL) {
            // Last element
            (metaArr[businessId].bsn)->bsntoindcus = NULL;
          } else {
            // Middle or first element
            (metaArr[businessId].bsn)->bsntoindcus = businessNodeCus->next;
          }
        } else {
          // Not first node, it's middle or last
          for (int j = 0; j < nofCustomers - 1; j++) {
            if ((((businessNodeCus->next)->ind)->cmn).id == givenId) {
              if (businessNodeCus->next->next == NULL) {
                // Last element
                businessNodeCus->next = NULL;
              } else {
                // Middle element
                businessNodeCus->next = businessNodeCus->next->next;
              }
              break;
            }
            businessNodeCus = businessNodeCus->next;
          }
        }
        // Decrease the count
        ((metaArr[businessId].bsn)->nofcus)--;
      }
    }

    // Delete traces from owners
    int numOwners = (metaArr[givenId].ind)->nofmofbsnown;
    for (int i = 0; i < numOwners; i++) {
      int ownerId = ((metaArr[givenId].ind)->mofbsncown)[i];
      if (ownerId >= 0) {
        indlist *businessNodeOwn = (metaArr[ownerId].bsn)->bsntoindown;
        int nofOwners = (metaArr[ownerId].bsn)->nofown;

        if (businessNodeOwn != NULL) {
          // Check and delete the node
          if (((businessNodeOwn->ind)->cmn).id == givenId) {
            if (businessNodeOwn->next == NULL) {
              // Last element
              (metaArr[ownerId].bsn)->bsntoindown = NULL;
            } else {
              // Middle or first element
              (metaArr[ownerId].bsn)->bsntoindown = businessNodeOwn->next;
            }
          } else {
            // Not first node, it's middle or last
            for (int j = 0; j < nofOwners - 1; j++) {
              if ((((businessNodeOwn->next)->ind)->cmn).id == givenId) {
                if (businessNodeOwn->next->next == NULL) {
                  // Last element
                  businessNodeOwn->next = NULL;
                } else {
                  // Middle element
                  businessNodeOwn->next = businessNodeOwn->next->next;
                }
                break;
              }
              businessNodeOwn = businessNodeOwn->next;
            }
          }
          // Decrease the count
          ((metaArr[ownerId].bsn)->nofown)--;
        }
      }
    }
  }
}

void deleteTracesOfOrganisation(int givenId) {
  indlist *node = (metaArr[givenId].org)->orgtoind;
  int nofm = (metaArr[givenId].org)->nofm;
  int noofm;
  for (int j = 0; j < nofm; j++) {
    noofm = ((node->ind)->nofmoforg);
    int orgid;
    //! some risk below
    for (int k = 0; k < noofm; k++) {
      orgid = ((node->ind)->moforg)[k];
      if (orgid == givenId) {
        ((node->ind)->moforg)[k] = -1;
        break;
      }
    }
    node = node->next;
  }
}

// Function to delete traces for businesses
void deleteTracesOfBusiness(int givenId) {
  // Remove traces from owners
  indlist *businessOwnerNode = (metaArr[givenId].bsn)->bsntoindown;
  int nofOwners = (metaArr[givenId].bsn)->nofown;

  for (int j = 0; j < nofOwners; j++) {
    int noofg = ((businessOwnerNode->ind)->nofmofbsnown);

    for (int k = 0; k < noofg; k++) {
      int businessId = ((businessOwnerNode->ind)->mofbsncown)[k];
      if (businessId == givenId) {
        ((businessOwnerNode->ind)->mofbsncown)[k] = -1;
        break;
      }
    }

    businessOwnerNode = businessOwnerNode->next;
  }

  // Remove traces from customers
  indlist *businessCustomerNode = (metaArr[givenId].bsn)->bsntoindcus;
  int nofCustomers = (metaArr[givenId].bsn)->nofcus;

  for (int j = 0; j < nofCustomers; j++) {
    int noofg = ((businessCustomerNode->ind)->nofmofbsncus);

    for (int k = 0; k < noofg; k++) {
      int businessId = ((businessCustomerNode->ind)->mofbsncus)[k];
      if (businessId == givenId) {
        ((businessCustomerNode->ind)->mofbsncus)[k] = -1;
        break;
      }
    }

    businessCustomerNode = businessCustomerNode->next;
  }

  // Delete traces from groups
  int numGroups = (metaArr[givenId].bsn)->nofmofgrp;
  for (int i = 0; i < numGroups; i++) {
    int groupId = ((metaArr[givenId].bsn)->mofgrp)[i];

    if (groupId >= 0) {
      bsnlist *groupNode = (metaArr[groupId].grp)->grptobsn;
      int nofMembersGroup = (metaArr[groupId].grp)->nofbm;
      if (groupNode != NULL) {
        // Check and delete the node
        if (((groupNode->bsn)->cmn).id == givenId) {
          if (groupNode->next == NULL) {
            // Last element
            (metaArr[groupId].grp)->grptobsn = NULL;
          } else {
            // Middle or first element
            (metaArr[groupId].grp)->grptobsn = groupNode->next;
          }
        } else {
          // Not first node, it's middle or last
          for (int j = 0; j < nofMembersGroup - 1; j++) {
            if ((((groupNode->next)->bsn)->cmn).id == givenId) {
              if (groupNode->next->next == NULL) {
                // Last element
                groupNode->next = NULL;
              } else {
                // Middle element
                groupNode->next = groupNode->next->next;
              }
              break;
            }
            groupNode = groupNode->next;
          }
        }
        // Decrease the count
        ((metaArr[groupId].grp)->nofbm)--;
      }
    }
  }
}

void deleteTracesOfGroup(int givenId) {
  // Delete traces from individuals
  indlist *groupNode = (metaArr[givenId].grp)->grptoind;
  int nofMembers = (metaArr[givenId].grp)->nofim;

  for (int j = 0; j < nofMembers; j++) {
    int noofg = ((groupNode->ind)->nofmofgrp);

    for (int k = 0; k < noofg; k++) {
      int groupId = ((groupNode->ind)->mofgrp)[k];
      if (groupId == givenId) {
        ((groupNode->ind)->mofgrp)[k] = -1;
        break;
      }
    }

    groupNode = groupNode->next;
  }
  // Delete traces from businesses
  bsnlist *groupNodeBsn = (metaArr[givenId].grp)->grptobsn;
  int nofBusinesses = (metaArr[givenId].grp)->nofbm;

  for (int j = 0; j < nofBusinesses; j++) {
    int noofg = ((groupNodeBsn->bsn)->nofmofgrp);

    for (int k = 0; k < noofg; k++) {
      int groupId = ((groupNodeBsn->bsn)->mofgrp)[k];
      if (groupId == givenId) {
        ((groupNodeBsn->bsn)->mofgrp)[k] = -1;
        break;
      }
    }

    groupNodeBsn = groupNodeBsn->next;
  }
}

void delete(int givenId) {
  if (givenId < id) {
    if (metaArr[givenId].present) {
      int type = metaArr[givenId].type;
      // find previous present, next present
      int prev = findPrev(givenId);
      int next = findNext(givenId);
      // link them
      if (type == 1) {
        // individual
        deleteTracesOfIndividual(givenId);
        if (next) {
          if (prev == -1) {
            individualListHead = metaArr[next].ind;
            individualListTail = metaArr[next].ind;
          } else {
            (metaArr[prev].ind)->next = metaArr[next].ind;
          }
        } else {
          // last element
          if (prev == -1) {
            individualListHead = NULL;
            individualListTail = NULL;
          } else {
            (metaArr[prev].ind)->next = NULL;
          }
        }
        // remove individual footprints
        nofi--;
      } else if (type == 2) {
        // group
        deleteTracesOfGroup(givenId);
        if (next) {
          if (prev == -1) {
            groupListHead = metaArr[next].grp;
            groupListTail = metaArr[next].grp;
          } else {
            (metaArr[prev].grp)->next = metaArr[next].grp;
          }
        } else {
          // last element
          if (prev == -1) {
            groupListHead = NULL;
            groupListTail = NULL;
          } else {
            (metaArr[prev].grp)->next = NULL;
          }
        }
        // remove group footprints
        nofg--;
      } else if (type == 3) {
        // business
        deleteTracesOfBusiness(givenId);
        if (next) {
          if (prev == -1) {
            businessListHead = metaArr[next].bsn;
            busninessListTail = metaArr[next].bsn;
          } else {
            (metaArr[prev].bsn)->next = metaArr[next].bsn;
          }
        } else {
          // last element
          if (prev == -1) {
            businessListHead = NULL;
            busninessListTail = NULL;
          } else {
            (metaArr[prev].bsn)->next = NULL;
          }
        }
        // remove business footprints
        nofb--;
      } else if (type == 4) {
        // organization
        deleteTracesOfOrganisation(givenId);
        if (next) {
          if (prev == -1) {
            organisationListHead = metaArr[next].org;
            organisationListTail = metaArr[next].org;
          } else {
            (metaArr[prev].org)->next = metaArr[next].org;
          }
        } else {
          // last element
          if (prev == -1) {
            organisationListHead = NULL;
            organisationListTail = NULL;
          } else {
            (metaArr[prev].org)->next = NULL;
          }
        }
        // remove organization footprints
        nofo--;
      }
      metaArr[givenId].present = 0;
    } else {
      printf("not found.\n");
    }
  } else {
    printf("Enter valid id\n");
  }
}

int searchByName() {
  char s[100];
  printf("Enter name: ");
  getchar();
  scanf("%[^\n]s", s);

  // Search in individuals
  individual *indCopy = individualListHead;
  for (int i = 0; i < nofi; i++) {
    if (!strcmp(s, (indCopy->cmn).name)) {
      return (indCopy->cmn).id;
    }
    indCopy = indCopy->next;
  }

  // Search in organisations
  organisation *orgCopy = organisationListHead;
  for (int i = 0; i < nofo; i++) {
    if (!strcmp(s, (orgCopy->cmn).name)) {
      return (orgCopy->cmn).id;
    }
    orgCopy = orgCopy->next;
  }

  // Search in groups
  group *grpCopy = groupListHead;
  for (int i = 0; i < nofg; i++) {
    if (!strcmp(s, (grpCopy->cmn).name)) {
      return (grpCopy->cmn).id;
    }
    grpCopy = grpCopy->next;
  }

  // Search in businesses
  business *bsnCopy = businessListHead;
  for (int i = 0; i < nofb; i++) {
    if (!strcmp(s, (bsnCopy->cmn).name)) {
      return (bsnCopy->cmn).id;
    }
    bsnCopy = bsnCopy->next;
  }

  return -1; // Not found
}

int searchByType() {
  // individual
  printf("Enter 1 for individual, 2 for group, 3 for bussiness and 4 for organisation : ");
  int type;
  scanf("%d", &type);
  if (type == 1) {
    individual *copy = individualListHead;
    for (int i = 0; i < nofi; i++) {
      printf("type: individual , id: %d , name: %s , birthday : %s\n", (copy->cmn).id, (copy->cmn).name, copy->birthDate);
      copy = copy->next;
    }
  } else if (type == 2) {
    group *copy = groupListHead;
    for (int i = 0; i < nofg; i++) {
      printf("type: individual , id: %d , name: %s\n", (copy->cmn).id, (copy->cmn).name);
      copy = copy->next;
    }
  } else if (type == 3) {
    business *copy = businessListHead;
    for (int i = 0; i < nofb; i++) {
      printf("type: group , id: %d , name: %s , location: (%d, %d)\n", (copy->cmn).id, (copy->cmn).name, (copy->location).x,(copy->location).y);
      copy = copy->next;
    }
  } else if (type == 4) {
    organisation *copy = organisationListHead;
    for (int i = 0; i < nofo; i++) {
      printf("type: business , id: %d , name: %s , location: (%d, %d)\n", (copy->cmn).id, (copy->cmn).name, (copy->location).x,(copy->location).y);
      copy = copy->next;
    }
  } else {
    printf("Enter valid option\n");
  }
};

int searchByBirthDay() {
  char s[100];
  printf("Enter birthday : ");
  getchar();
  scanf("%[^\n]s", s);
  individual *copy = individualListHead;
  for (int i = 0; i < nofi; i++) {
    if (!strcmp(s, (copy)->birthDate)) {
      return (copy->cmn).id;
    }
    copy = copy->next;
  }
  return -1;
};

void printLinkedNodes() {
  int givenId;
  printf("Enter the ID of the node you want 1-hop linked nodes to: ");
  scanf("%d", &givenId);

  if (isIdPresent(givenId)) {
    int type = metaArr[givenId].type;

    if (type == 1) {
      // Individual node
      printf("There are no links for any individual.\n");
    } else if (type == 2) {
      // Group node
      indlist *indNode = (metaArr[givenId].grp)->grptoind;
      int nofi = (metaArr[givenId].grp)->nofim;
      int indId;
      for (int j = 0; j < nofi; j++) {
        indId = ((indNode->ind)->cmn).id;
        printf("Linked type: individual (Individual Member), ID: %d, Name: %s\n", indId, ((metaArr[indId].ind)->cmn).name);
        indNode = indNode->next;
      }

      bsnlist *bsnNode = (metaArr[givenId].grp)->grptobsn;
      int nofb = (metaArr[givenId].grp)->nofbm;
      int bsnId;
      for (int j = 0; j < nofb; j++) {
        bsnId = ((bsnNode->bsn)->cmn).id;
        printf("Linked type: business (Business Member), ID: %d, Name: %s\n", bsnId, ((metaArr[bsnId].bsn)->cmn).name);
        bsnNode = bsnNode->next;
      }
    } else if (type == 3) {
      // Business node
      indlist *indNodeCus = (metaArr[givenId].bsn)->bsntoindcus;
      int nofiCus = (metaArr[givenId].bsn)->nofcus;
      int indIdCus;
      for (int j = 0; j < nofiCus; j++) {
        indIdCus = ((indNodeCus->ind)->cmn).id;
        printf("Linked type: individual (Customer), ID: %d, Name: %s\n", indIdCus, ((metaArr[indIdCus].ind)->cmn).name);
        indNodeCus = indNodeCus->next;
      }

      indlist *indNodeOwn = (metaArr[givenId].bsn)->bsntoindown;
      int nofiOwn = (metaArr[givenId].bsn)->nofown;
      int indIdOwn;
      for (int j = 0; j < nofiOwn; j++) {
        indIdOwn = ((indNodeOwn->ind)->cmn).id;
        printf("Linked type: individual (Owner), ID: %d, Name: %s\n", indIdOwn, ((metaArr[indIdOwn].ind)->cmn).name);
        indNodeOwn = indNodeOwn->next;
      }
    } else if (type == 4) {
      // Organisation node
      indlist *indNode = (metaArr[givenId].org)->orgtoind;
      int nofiOrg = (metaArr[givenId].org)->nofm;
      int indId;
      for (int j = 0; j < nofiOrg; j++) {
        indId = ((indNode->ind)->cmn).id;
        printf("Linked type: individual, ID: %d, Name: %s\n", indId, ((metaArr[indId].ind)->cmn).name);
        indNode = indNode->next;
      }
    } else {
      printf("Enter a valid type.\n");
    }
  } else {
    printf("Invalid ID.\n");
  }
}

//! content here is only one content you will want multiple content
void createContent() {
  int givenId;
  printf("Enter id of node you want to createContent content to : ");
  scanf("%d", &givenId);
  if (isIdPresent(givenId)) {
    int type = metaArr[givenId].type;
    if (type == 1) {
      printf("Enter content as a string : ");
      getchar();
      scanf("%[^\n]s", ((metaArr[givenId].ind)->cmn).content);
      // printf("\n\n\n\ncontent is set to %s\n\n\n\n", ((metaArr[givenId].ind)->cmn).content);
    } else if (type == 2) {
      printf("Enter content as a string : ");
      getchar();
      scanf("%[^\n]s", ((metaArr[givenId].grp)->cmn).content);
    } else if (type == 3) {
      printf("Enter content as a string : ");
      getchar();
      scanf("%[^\n]s", ((metaArr[givenId].bsn)->cmn).content);
    } else if (type == 4) {
      printf("Enter content as a string : ");
      getchar();
      scanf("%[^\n]s", ((metaArr[givenId].org)->cmn).content);
    } else {
      printf("Enter valid type.\n");
    }
  } else {
    printf("invalid id.\n");
  }
};
void printContentByNode(int givenId) {
  if (isIdPresent(givenId)) {
    int type = metaArr[givenId].type;
    if (type == 1) {
      if (((metaArr[givenId].ind)->cmn).content[0] == '\0')
        printf("no content by %s.\n", ((metaArr[givenId].ind)->cmn).name);
      else
        printf("content is : \"%s\" by %s.\n", ((metaArr[givenId].ind)->cmn).content, ((metaArr[givenId].ind)->cmn).name);
    } else if (type == 2) {
      if (((metaArr[givenId].grp)->cmn).content[0] == '\0')
        printf("no content by %s.\n", ((metaArr[givenId].grp)->cmn).name);
      else
        printf("content is : \"%s\" by %s.\n", ((metaArr[givenId].grp)->cmn).content, ((metaArr[givenId].grp)->cmn).name);
    } else if (type == 3) {
      if (((metaArr[givenId].bsn)->cmn).content[0] == '\0')
        printf("no content by %s.\n", ((metaArr[givenId].bsn)->cmn).name);
      else
        printf("content is : \"%s\" by %s.\n", ((metaArr[givenId].bsn)->cmn).content, ((metaArr[givenId].bsn)->cmn).name);
    } else if (type == 4) {
      if (((metaArr[givenId].org)->cmn).content[0] == '\0')
        printf("no content by %s.\n", ((metaArr[givenId].org)->cmn).name);
      else
        printf("content is :\"%s\" by %s.\n", ((metaArr[givenId].org)->cmn).content, ((metaArr[givenId].org)->cmn).name);
    } else {
      printf("Enter valid type.\n");
    }
  } else {
    printf("invalid id.\n");
  }
};

void printContentByLinkedNodes() {
  int givenId;
  printf("Enter the ID of the individual to get the content of linked persons: ");
  scanf("%d", &givenId);

  if (isIdPresent(givenId)) {
    int type = metaArr[givenId].type;

    if (type == 1) {
      // Individual node
      // Posts by linked organizations
      int numOrgs = (metaArr[givenId].ind)->nofmoforg;
      for (int i = 0; i < numOrgs; i++) {
        int orgId = ((metaArr[givenId].ind)->moforg)[i];
        if (orgId >= 0) {
          indlist *orgNode = (metaArr[orgId].org)->orgtoind;
          int nofMembers = (metaArr[orgId].org)->nofm;
          for (int j = 0; j < nofMembers; j++) {
            if (((orgNode->ind)->cmn).id != givenId) {
              printContentByNode(((orgNode->ind)->cmn).id);
            }
            orgNode = orgNode->next;
          }
        }
      }

      // Posts by linked groups
      int numGroups = (metaArr[givenId].ind)->nofmofgrp;
      for (int i = 0; i < numGroups; i++) {
        int groupId = ((metaArr[givenId].ind)->mofgrp)[i];
        if (groupId >= 0) {
          indlist *groupNode = (metaArr[groupId].grp)->grptoind;
          int nofMembers = (metaArr[groupId].grp)->nofim;
          for (int j = 0; j < nofMembers; j++) {
            if (((groupNode->ind)->cmn).id != givenId) {
              printContentByNode(((groupNode->ind)->cmn).id);
            }
            groupNode = groupNode->next;
          }
        }
      }
    } else {
      printf("Enter only an individual's ID.\n");
    }
  } else {
    printf("Invalid ID.\n");
  }
}

int masterInterface() {
  // show all nodes, ind only now
  individual *copyind = individualListHead;
  organisation *copyorg = organisationListHead;
  group *copygrp = groupListHead;
  business *copybsn = businessListHead;

  // printf("\n--------> All Nodes Present <---------\n");
  printf("\nAll Nodes Present\n\n");

  for (int i = 0; i < nofi; i++) {
    printf("Type: Individual, ID: %d, Name: %s, Birthday: %s\n", (copyind->cmn).id, (copyind->cmn).name, (copyind->birthDate));
    copyind = copyind->next;
  }

  for (int i = 0; i < nofo; i++) {
    printf("Type: Organisation, ID: %d, Name: %s, Location: (%d, %d)\n", (copyorg->cmn).id, (copyorg->cmn).name, (copyorg->location).x, (copyorg->location).y);
    copyorg = copyorg->next;
  }

  for (int i = 0; i < nofg; i++) {
    printf("Type: Group, ID: %d, Name: %s\n", (copygrp->cmn).id, (copygrp->cmn).name);
    copygrp = copygrp->next;
  }

  for (int i = 0; i < nofb; i++) {
    printf("Type: Business, ID: %d, Name: %s, Location: (%d, %d)\n", (copybsn->cmn).id, (copybsn->cmn).name, (copybsn->location).x, (copybsn->location).y);
    copybsn = copybsn->next;
  }

  int x;
  printf("1. Create and delete nodes of each type.\n");
  printf("2. Search for nodes using the name or type or birthday.\n");
  printf("3. Print all 1-hop linked nodes to a given input node.\n");
  printf("4. Create and createContent content by a node.\n");
  printf("5. Search for content createContented by any node.\n");
  printf("6. Display all content createContented by nodes linked to a given node.\n");
  printf("7. Exit.\n");
  printf("Enter your choice (1-7): ");
  scanf("%d", &x);
  // printf("              content          \n");
  if (x == 7)
    return 0;
  return x;
};
int main() {
  int x = 1;
  individualListHead = NULL;
  organisationListHead = NULL;
  individualListTail = NULL;
  organisationListTail = NULL;
  groupListHead = NULL;
  businessListHead = NULL;
  groupListTail = NULL;
  busninessListTail = NULL;
  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);
  do {
    x = masterInterface();
    if (x == 1) {
      int y;
      printf("Enter 1 for creating and 2 for deleting: ");
      scanf("%d", &y);
      if (y == 1) {
        // create
        create();
      } else if (y == 2) {
        // delete
        int givenId;
        printf("Enter id : ");
        scanf("%d", &givenId);
        delete (givenId);
      } else {
        printf("Enter valid option\n");
      }
      printf("\n");

    } else if (x == 2) {
      int w;
      printf("Enter 1 for search by name, 2 for search by type, 3 for seach by birthday :");
      scanf("%d", &w);
      if (w == 1) {
        int fetchid = searchByName();
        if (fetchid == -1) {
          printf("no match for your input\n");
        } else {
          printf("matched for id %d\n", fetchid);
        }
      } else if (w == 2) {
        searchByType();
      } else if (w == 3) {
        int fetchid = searchByBirthDay();
        if (fetchid == -1) {
          printf("no match for your input\n");
        } else {
          printf("matched for id %d with name %s\n", fetchid, ((metaArr[fetchid].ind)->cmn).name);
        }
      } else {
        printf("Enter valid option.\n");
      }
    } else if (x == 3) {
      printLinkedNodes();
    } else if (x == 4) {
      createContent();
    } else if (x == 5) {
      int givenId;
      printf("Enter id of node you want to see content of : ");
      scanf("%d", &givenId);
      printContentByNode(givenId);
    } else if (x == 6) {
      printContentByLinkedNodes();
    } else if (x == 0) {
      printf("exiting..\n");
    } else {
      printf("Invalid choice. Please enter a number between 1 and 6.\n");
    }
  } while (x);

  return 0;
}