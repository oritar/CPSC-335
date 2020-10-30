## CPSC 335 - Project 1
### Members:
---
    Tracy Origel exmachinima@csu.fullerton.edu
    Maria Diaz   mardiaz353@csu.fullerton.edu

### Algorithm Design:
---
> left-to-right Pseudocode
    define object(DISKS) // where DISKS hold light and dark disks
    int counter = 0;     // tracks total count of swaps

    for i = 0 to number of light disks {
        for j = 0 to number of total disks - 1 {
            if DISKS[j] is a light disk && DISKS[j + 1] is not a dark disk {
                swap(DISKS[j], DISKS[j + 1]);
                counter++;
            }
        }
    }

    return sorted DISKS;

> lawnmower Pseudocode

    