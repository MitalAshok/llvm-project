; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -mtriple=aarch64-linux-gnu -mattr=+sme2 -force-streaming -verify-machineinstrs < %s | FileCheck %s

; MOPA/MOPS

define void @outer_sum_accumulate_s16(<vscale x 8 x i1> %pn, <vscale x 8 x i1> %pm, <vscale x 8 x i16> %zn, <vscale x 8 x i16> %zm) {
; CHECK-LABEL: outer_sum_accumulate_s16:
; CHECK:       // %bb.0:
; CHECK-NEXT:    smopa za3.s, p0/m, p1/m, z0.h, z1.h
; CHECK-NEXT:    ret
  call void @llvm.aarch64.sme.smopa.za32.nxv8i16(i32 3, <vscale x 8 x i1> %pn, <vscale x 8 x i1> %pm, <vscale x 8 x i16> %zn, <vscale x 8 x i16> %zm)
  ret void
}

define void @outer_sum_accumulate_u16(<vscale x 8 x i1> %pn, <vscale x 8 x i1> %pm, <vscale x 8 x i16> %zn, <vscale x 8 x i16> %zm) {
; CHECK-LABEL: outer_sum_accumulate_u16:
; CHECK:       // %bb.0:
; CHECK-NEXT:    umopa za3.s, p0/m, p1/m, z0.h, z1.h
; CHECK-NEXT:    ret
  call void @llvm.aarch64.sme.umopa.za32.nxv8i16(i32 3, <vscale x 8 x i1> %pn, <vscale x 8 x i1> %pm, <vscale x 8 x i16> %zn, <vscale x 8 x i16> %zm)
  ret void
}

define void @outer_sum_subtract_s16(<vscale x 8 x i1> %pn, <vscale x 8 x i1> %pm, <vscale x 8 x i16> %zn, <vscale x 8 x i16> %zm) {
; CHECK-LABEL: outer_sum_subtract_s16:
; CHECK:       // %bb.0:
; CHECK-NEXT:    smops za3.s, p0/m, p1/m, z0.h, z1.h
; CHECK-NEXT:    ret
  call void @llvm.aarch64.sme.smops.za32.nxv8i16(i32 3, <vscale x 8 x i1> %pn, <vscale x 8 x i1> %pm, <vscale x 8 x i16> %zn, <vscale x 8 x i16> %zm)
  ret void
}

define void @outer_sum_subtract_u16(<vscale x 8 x i1> %pn, <vscale x 8 x i1> %pm, <vscale x 8 x i16> %zn, <vscale x 8 x i16> %zm) {
; CHECK-LABEL: outer_sum_subtract_u16:
; CHECK:       // %bb.0:
; CHECK-NEXT:    umops za3.s, p0/m, p1/m, z0.h, z1.h
; CHECK-NEXT:    ret
  call void @llvm.aarch64.sme.umops.za32.nxv8i16(i32 3, <vscale x 8 x i1> %pn, <vscale x 8 x i1> %pm, <vscale x 8 x i16> %zn, <vscale x 8 x i16> %zm)
  ret void
}

;
; BMOPA/BMOPS
;

define void @bitwise_outer_sum_accumulate_u32(<vscale x 4 x i1> %pn, <vscale x 4 x i1> %pm, <vscale x 4 x i32> %zn, <vscale x 4 x i32> %zm) {
; CHECK-LABEL: bitwise_outer_sum_accumulate_u32:
; CHECK:       // %bb.0:
; CHECK-NEXT:    bmopa za3.s, p0/m, p1/m, z0.s, z1.s
; CHECK-NEXT:    ret
  call void @llvm.aarch64.sme.bmopa.za32.nxv4i32(i32 3, <vscale x 4 x i1> %pn, <vscale x 4 x i1> %pm, <vscale x 4 x i32> %zn, <vscale x 4 x i32> %zm)
  ret void
}

define void @bitwise_outer_sum_subtract_u32(<vscale x 4 x i1> %pn, <vscale x 4 x i1> %pm, <vscale x 4 x i32> %zn, <vscale x 4 x i32> %zm) {
; CHECK-LABEL: bitwise_outer_sum_subtract_u32:
; CHECK:       // %bb.0:
; CHECK-NEXT:    bmops za3.s, p0/m, p1/m, z0.s, z1.s
; CHECK-NEXT:    ret
  call void @llvm.aarch64.sme.bmops.za32.nxv4i32(i32 3, <vscale x 4 x i1> %pn, <vscale x 4 x i1> %pm, <vscale x 4 x i32> %zn, <vscale x 4 x i32> %zm)
  ret void
}

declare void @llvm.aarch64.sme.smopa.za32.nxv8i16(i32, <vscale x 8 x i1>, <vscale x 8 x i1>, <vscale x 8 x i16>, <vscale x 8 x i16>)
declare void @llvm.aarch64.sme.umopa.za32.nxv8i16(i32, <vscale x 8 x i1>, <vscale x 8 x i1>, <vscale x 8 x i16>, <vscale x 8 x i16>)

declare void @llvm.aarch64.sme.smops.za32.nxv8i16(i32, <vscale x 8 x i1>, <vscale x 8 x i1>, <vscale x 8 x i16>, <vscale x 8 x i16>)
declare void @llvm.aarch64.sme.umops.za32.nxv8i16(i32, <vscale x 8 x i1>, <vscale x 8 x i1>, <vscale x 8 x i16>, <vscale x 8 x i16>)

declare void @llvm.aarch64.sme.bmopa.za32.nxv4i32(i32, <vscale x 4 x i1>, <vscale x 4 x i1>, <vscale x 4 x i32>, <vscale x 4 x i32>)
declare void @llvm.aarch64.sme.bmops.za32.nxv4i32(i32, <vscale x 4 x i1>, <vscale x 4 x i1>, <vscale x 4 x i32>, <vscale x 4 x i32>)

