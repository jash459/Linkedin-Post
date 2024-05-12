# To Create and Extend logical volumes by using LVM on Ubuntu 21.04

1. Step 1: Check the installed OS version by using the following command
```
root@linuxhelp:~# lsb_release -a
No LSB modules are available.
Distributor ID:	Ubuntu
Description:	Ubuntu 21.04
Release:	21.04
Codename:	hirsute
```

2. Step 2: List all physical disk available in system by using the following command

```
root@linuxhelp:~# fdisk -l | grep /dev/sd
Disk /dev/sdc: 15 GiB, 16106127360 bytes, 31457280 sectors
Disk /dev/sdd: 10 GiB, 10737418240 bytes, 20971520 sectors
Disk /dev/sdb: 10 GiB, 10737418240 bytes, 20971520 sectors
Disk /dev/sda: 40 GiB, 42949672960 bytes, 83886080 sectors
/dev/sda1   2048    4095    2048    1M BIOS boot
/dev/sda2   4096 1054719 1050624  513M EFI System
```

3. Step 3: Step 3: Open fdisk to create partions on /dev/sdb disk

```
root@linuxhelp:~# fdisk /dev/sdb

Welcome to fdisk (util-linux 2.36.1).
Changes will remain in memory only, until you decide to write them.
Be careful before using the write command.

Create New Partition
Command (m for help): n
Partition type
   p   primary (0 primary, 0 extended, 4 free)
   e   extended (container for logical partitions)
Select (default p): 

Using default response p.

Using default partition number and using entire disk space partition by pressing enter for all
Partition number (1-4, default 1): 
First sector (2048-20971519, default 2048): 
Last sector, +/-sectors or +/-size{K,M,G,T,P} (2048-20971519, default 20971519): 

Created a new partition 1 of type 'Linux' and of size 10 GiB.




Change the partition type to Linux LVM 
Command (m for help): t

Selected partition 1
Hex code or alias (type L to list all): 8E
Changed type of partition 'Linux' to 'Linux LVM'.

View the created partition
Command (m for help): p
Disk /dev/sdb: 10 GiB, 10737418240 bytes, 20971520 sectors
Disk model: VMware Virtual S
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0x5da27853

Device     Boot Start      End  Sectors Size Id Type
/dev/sdb1        2048 20971519 20969472  10G 8e Linux LVM


Save the all changes made to the disks
Command (m for help): w
The partition table has been altered.
Calling ioctl() to re-read partition table.
Syncing disks.
```

4. Step 4: Step 4: Open fdisk to create partions on /dev/sdc disk



```
root@linuxhelp:~# fdisk /dev/sdc

Welcome to fdisk (util-linux 2.36.1).
Changes will remain in memory only, until you decide to write them.
Be careful before using the write command.

Create New Partition
Command (m for help): n
Partition type
   p   primary (0 primary, 0 extended, 4 free)
   e   extended (container for logical partitions)
Select (default p): 

Using default response p.


Using default partition number and using entire disk space partition by pressing enter for all
Partition number (1-4, default 1): 
First sector (2048-31457279, default 2048): 
Last sector, +/-sectors or +/-size{K,M,G,T,P} (2048-31457279, default 31457279): 

Created a new partition 1 of type 'Linux' and of size 15 GiB.


Change the partition type to Linux LVM 
Command (m for help): t
Selected partition 1
Hex code or alias (type L to list all): 8E
Changed type of partition 'Linux' to 'Linux LVM'.


View the created partition
Command (m for help): p

Disk /dev/sdc: 15 GiB, 16106127360 bytes, 31457280 sectors
Disk model: VMware Virtual S
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0xfe1d405a

Device     Boot Start      End  Sectors Size Id Type
/dev/sdc1        2048 31457279 31455232  15G 8e Linux LVM

Save  the all changes made to the disks
Command (m for help): w
The partition table has been altered.
Calling ioctl() to re-read partition table.
Syncing disks.
```

5. Step 5: Create physical volume in /dev/sdb1 drive
```
root@linuxhelp:~# pvcreate /dev/sdb1
  Physical volume "/dev/sdb1" successfully created.
```

6. Step 6: Create physical volume in /dev/sdc1 drive
```
root@linuxhelp:~# pvcreate /dev/sdc1
  Physical volume "/dev/sdc1" successfully created.
```

7. Step 7: List the physical volume by using the following command
```
root@linuxhelp:~# pvs
  PV         VG Fmt  Attr PSize   PFree  
  /dev/sdb1     lvm2 ---  <10.00g <10.00g
  /dev/sdc1     lvm2 ---  <15.00g <15.00g
```

8. Step 8: Create the volume group named “myvg” with PVs contained
```
root@linuxhelp:~# vgcreate myvg /dev/sdb1 /dev/sdc1
  Volume group "myvg" successfully created
```

9. Step 9: List the volume group by using the following command
```
root@linuxhelp:~# vgs
  VG   #PV #LV #SN Attr   VSize  VFree 
  myvg   2   0   0 wz--n- 24.99g 24.99g
```

10. Step 10: Create logical volume named “mylv” with 20GB size in volume group “myvg”
```
root@linuxhelp:~# lvcreate -L 20G -n mylv myvg
WARNING: ext4 signature detected on /dev/myvg/mylv at offset 1080. Wipe it? [y/n]: y
  Wiping ext4 signature on /dev/myvg/mylv.
  Logical volume "mylv" created.
```

11. Step 11: View the volume group with details
```
root@linuxhelp:~# lvdisplay myvg
  --- Logical volume ---
  LV Path                /dev/myvg/mylv
  LV Name                mylv
  VG Name                myvg
  LV UUID                3s0Afz-7d2Q-Yhcp-rcbO-KozC-2qo0-QadjMr
  LV Write Access        read/write
  LV Creation host, time linuxhelp, 2021-11-13 00:59:16 +0530
  LV Status              available
  open                 0
 LV Size                20.00 GiB
  Current LE             5120
  Segments               2
  Allocation             inherit
  Read ahead sectors     auto
  - currently set to     256
  Block device           253:0
```

12. Step 12: Format the logical volume “mylv” to ext4 file system
```
root@linuxhelp:~# mkfs.ext4 /dev/myvg/mylv
mke2fs 1.45.7 (28-Jan-2021)
Creating filesystem with 5242880 4k blocks and 1310720 inodes
Filesystem UUID: f26aa915-2f06-44cf-92fd-8202b05d7408
Superblock backups stored on blocks: 
	32768, 98304, 163840, 229376, 294912, 819200, 884736, 1605632, 2654208, 
	4096000

Allocating group tables: done                            
Writing inode tables: done                            
Creating journal (32768 blocks): done
Writing superblocks and filesystem accounting information: done 
```

13. Step 13: Mount the logical volume “mylv” to the directory /mnt
```
root@linuxhelp:~# mount /dev/myvg/mylv /mnt
```

14. Step 14: Viewing the mounted status by using following command
```
root@linuxhelp:~# df -h
Filesystem             Size  Used Avail Use% Mounted on
tmpfs                  195M  1.6M  194M   1% /run
/dev/sda3               39G  9.7G   27G  27% /
tmpfs                  974M     0  974M   0% /dev/shm
tmpfs                  5.0M  4.0K  5.0M   1% /run/lock
tmpfs                  4.0M     0  4.0M   0% /sys/fs/cgroup
/dev/sda2              512M  5.3M  507M   2% /boot/efi
tmpfs                  195M  116K  195M   1% /run/user/1000
/dev/mapper/myvg-mylv   20G   45M   19G   1% /mnt
```

15. Step 15: Open the fdisk to create partions on /dev/sdc disk
```
root@linuxhelp:~# fdisk /dev/sdd

Welcome to fdisk (util-linux 2.36.1).
Changes will remain in memory only, until you decide to write them.
Be careful before using the write command.

Create New Partition
Command (m for help): n
Partition type
   p   primary (0 primary, 0 extended, 4 free)
   e   extended (container for logical partitions)
Select (default p): 

Using default response p.

Using default partition number and using entire disk space partition by pressing enter for all
Partition number (1-4, default 1): 
First sector (2048-20971519, default 2048): 
Last sector, +/-sectors or +/-size{K,M,G,T,P} (2048-20971519, default 20971519): 

Created a new partition 1 of type 'Linux' and of size 10 GiB.


Change the partition type to Linux LVM 
Command (m for help): t

Selected partition 1
Hex code or alias (type L to list all): 8E
Changed type of partition 'Linux' to 'Linux LVM'.

Save all the  changes made to the disks
Command (m for help): w

The partition table has been altered.
Calling ioctl() to re-read partition table.
Syncing disks.
```

16. Step 16: Extend the volume group with “/dev/sdd1” drive
```
root@linuxhelp:~# vgextend myvg /dev/sdd1
  Physical volume "/dev/sdd1" successfully created.
  Volume group "myvg" successfully extended
```

17. Step 17: List the volume group reflected that the 10 GB increased
```
root@linuxhelp:~# vgs
  VG   #PV #LV #SN Attr   VSize   VFree  
  myvg   3   1   0 wz--n- <34.99g <14.99g
```

18. Step 18: Extend the “mylv” logical volume by 10GB
```
root@linuxhelp:~# lvextend -L +10G /dev/myvg/mylv
  Size of logical volume myvg/mylv changed from 20.00 GiB (5120 extents) to 30.00 GiB (7680 extents).
  Logical volume myvg/mylv successfully resized.
```

19. Step 19: Use resize2fs command to change effect on logical volume
```
root@linuxhelp:~# resize2fs /dev/myvg/mylv
resize2fs 1.45.7 (28-Jan-2021)
Filesystem at /dev/myvg/mylv is mounted on /mnt; on-line resizing required
old_desc_blocks = 3, new_desc_blocks = 4
The filesystem on /dev/myvg/mylv is now 7864320 (4k) blocks long.
```

20. Step 20: List the mounted drives to see the changes in memory
```
root@linuxhelp:~# df -h
Filesystem             Size  Used Avail Use% Mounted on
tmpfs                  195M  1.6M  194M   1% /run
/dev/sda3               39G  9.7G   27G  27% /
tmpfs                  974M     0  974M   0% /dev/shm
tmpfs                  5.0M  4.0K  5.0M   1% /run/lock
tmpfs                  4.0M     0  4.0M   0% /sys/fs/cgroup
/dev/sda2              512M  5.3M  507M   2% /boot/efi
tmpfs                  195M  116K  195M   1% /run/user/1000
/dev/mapper/myvg-mylv   30G   44M   28G   1% /mnt
```

with this creation of logical volumes by using LVM on Ubuntu 21.04 comes to an end

