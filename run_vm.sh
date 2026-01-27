#!/bin/bash

qemu-system-x86_64 \
  -enable-kvm \
  -m 2048 \
  -cpu host \
  -smp 2 \
  -drive file=arch.qcow2,format=qcow2 \
  -device virtio-net-pci,netdev=net0 \
  -netdev user,id=net0,hostfwd=tcp::2222-:22 \
  -fsdev local,id=sharedfolder,path=wmfiles,security_model=passthrough \
  -device virtio-9p-pci,fsdev=sharedfolder,mount_tag=hostshare
