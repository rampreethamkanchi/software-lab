int numOrgs = (arr[givenId].ind)->nofmoforg;
  // for (int i = 0; i < numOrgs; i++) {
  //   int orgId = ((arr[givenId].ind)->moforg)[i];
  //   indlist *orgNode = (arr[orgId].org)->orgtoind;
  //   int nofMembersOrg = (arr[orgId].org)->nofm;

  //   if (orgNode != NULL) {
  //     // Check and delete the node
  //     if (((orgNode->ind)->cmn).id == givenId) {
  //       if (orgNode->next == NULL) {
  //         // Last element
  //         (arr[orgId].org)->orgtoind = NULL;
  //       } else {
  //         // Middle or first element
  //         (arr[orgId].org)->orgtoind = orgNode->next;
  //       }
  //     } else {
  //       // Not first node, it's middle or last
  //       for (int j = 0; j < nofMembersOrg - 1; j++) {
  //         if ((((orgNode->next)->ind)->cmn).id == givenId) {
  //           if (orgNode->next->next == NULL) {
  //             // Last element
  //             orgNode->next = NULL;
  //           } else {
  //             // Middle element
  //             orgNode->next = orgNode->next->next;
  //           }
  //           break;
  //         }
  //         orgNode = orgNode->next;
  //       }
  //     }
  //     // Decrease the count
  //     ((arr[orgId].org)->nofm)--;
  //   }
  // }

  // // Delete traces from groups
  // int numGroups = (arr[givenId].ind)->nofmofgrp;
  // for (int i = 0; i < numGroups; i++) {
  //   int groupId = ((arr[givenId].ind)->mofgrp)[i];
  //   indlist *groupNode = (arr[groupId].grp)->grptoind;
  //   int nofMembersGroup = (arr[groupId].grp)->nofim;

  //   if (groupNode != NULL) {
  //     // Check and delete the node
  //     if (((groupNode->ind)->cmn).id == givenId) {
  //       if (groupNode->next == NULL) {
  //         // Last element
  //         (arr[groupId].grp)->grptoind = NULL;
  //       } else {
  //         // Middle or first element
  //         (arr[groupId].grp)->grptoind = groupNode->next;
  //       }
  //     } else {
  //       // Not first node, it's middle or last
  //       for (int j = 0; j < nofMembersGroup - 1; j++) {
  //         if ((((groupNode->next)->ind)->cmn).id == givenId) {
  //           if (groupNode->next->next == NULL) {
  //             // Last element
  //             groupNode->next = NULL;
  //           } else {
  //             // Middle element
  //             groupNode->next = groupNode->next->next;
  //           }
  //           break;
  //         }
  //         groupNode = groupNode->next;
  //       }
  //     }
  //     // Decrease the count
  //     ((arr[groupId].grp)->nofim)--;
  //   }
  // }

  // // Delete traces from businesses
  // int numBusinesses = (arr[givenId].ind)->nofmofbsncus;
  // for (int i = 0; i < numBusinesses; i++) {
  //   int businessId = ((arr[givenId].ind)->mofbsncus)[i];
  //   indlist *businessNodeCus = (arr[businessId].bsn)->bsntoindcus;
  //   int nofCustomers = (arr[businessId].bsn)->nofcus;

  //   if (businessNodeCus != NULL) {
  //     // Check and delete the node
  //     if (((businessNodeCus->ind)->cmn).id == givenId) {
  //       if (businessNodeCus->next == NULL) {
  //         // Last element
  //         (arr[businessId].bsn)->bsntoindcus = NULL;
  //       } else {
  //         // Middle or first element
  //         (arr[businessId].bsn)->bsntoindcus = businessNodeCus->next;
  //       }
  //     } else {
  //       // Not first node, it's middle or last
  //       for (int j = 0; j < nofCustomers - 1; j++) {
  //         if ((((businessNodeCus->next)->ind)->cmn).id == givenId) {
  //           if (businessNodeCus->next->next == NULL) {
  //             // Last element
  //             businessNodeCus->next = NULL;
  //           } else {
  //             // Middle element
  //             businessNodeCus->next = businessNodeCus->next->next;
  //           }
  //           break;
  //         }
  //         businessNodeCus = businessNodeCus->next;
  //       }
  //     }
  //     // Decrease the count
  //     ((arr[businessId].bsn)->nofcus)--;
  //   }

  //   // Delete traces from owners
  //   int numOwners = (arr[givenId].ind)->nofmofbsnown;
  //   for (int i = 0; i < numOwners; i++) {
  //     int ownerId = ((arr[givenId].ind)->mofbsncown)[i];
  //     indlist *businessNodeOwn = (arr[ownerId].bsn)->bsntoindown;
  //     int nofOwners = (arr[ownerId].bsn)->nofown;

  //     if (businessNodeOwn != NULL) {
  //       // Check and delete the node
  //       if (((businessNodeOwn->ind)->cmn).id == givenId) {
  //         if (businessNodeOwn->next == NULL) {
  //           // Last element
  //           (arr[ownerId].bsn)->bsntoindown = NULL;
  //         } else {
  //           // Middle or first element
  //           (arr[ownerId].bsn)->bsntoindown = businessNodeOwn->next;
  //         }
  //       } else {
  //         // Not first node, it's middle or last
  //         for (int j = 0; j < nofOwners - 1; j++) {
  //           if ((((businessNodeOwn->next)->ind)->cmn).id == givenId) {
  //             if (businessNodeOwn->next->next == NULL) {
  //               // Last element
  //               businessNodeOwn->next = NULL;
  //             } else {
  //               // Middle element
  //               businessNodeOwn->next = businessNodeOwn->next->next;
  //             }
  //             break;
  //           }
  //           businessNodeOwn = businessNodeOwn->next;
  //         }
  //       }
  //       // Decrease the count
  //       ((arr[ownerId].bsn)->nofown)--;
  //     }
  //   }
  // }