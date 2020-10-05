
;; Function () (_ZN8MyThreadC1Ev, funcdef_no=0, decl_uid=217, cgraph_uid=0, symbol_order=1)

() (struct MyThread * D.404)
{
  void * #ref#1#2;
  struct java.lang.Object * D.409;
  void * #ref#0#0;
  void * _ref_1_2.0;

  D.409 = D.404;
  #ref#1#2 = D.409;
  _ref_1_2.0 = #ref#1#2;
   (_ref_1_2.0);
  goto <D.1359>;
  <D.1359>:
  return;
}



;; Function MyThread.run() (_ZN8MyThread3runEJvv, funcdef_no=1, decl_uid=218, cgraph_uid=1, symbol_order=2)

MyThread.run() (struct MyThread * D.413)
{
  void * D.1397;
  struct 
  {
    struct java.lang.Class * class;
    void * methods[2];
  } * D.1396;
  void * D.1395;
  void * D.1392;
  struct 
  {
    struct java.lang.Class * class;
    void * methods[2];
  } * D.1391;
  struct java.util.concurrent.Semaphore * D.1390;
  void * D.1389;
  struct 
  {
    struct java.lang.Class * class;
    void * methods[2];
  } * D.1388;
  void * D.1387;
  struct 
  {
    struct java.lang.Class * class;
    void * methods[2];
  } * D.1386;
  struct java.util.concurrent.Semaphore * D.1385;
  struct java.lang.Object * D.426;
  struct java.util.concurrent.Semaphore * D.430;
  struct java.io.PrintStream * D.912;
  struct java.lang.Object * D.1020;
  struct java.util.concurrent.Semaphore * D.1021;
  int D.1022;
  struct java.lang.Throwable * D.1070;
  void * #ref#1#13;
  void * #exc_obj;
  int #slot#3#10;
  void * #ref#3#9;
  void * #ref#2#4;
  void * #ref#0#2;
  int #slot#1#1;
  int #slot#2#0;
  boolean D.910;
  void java.lang.Throwable::<T421> (struct java.lang.Throwable *) * D.1383;
  void * D.1382;
  void * * D.1381;
  struct 
  {
    struct java.lang.Class * class;
    void * methods[2];
  } * D.1380;
  void * _ref_2_4.4;
  void java.util.concurrent.Semaphore::<T1c8> (struct java.util.concurrent.Semaphore *) * D.1377;
  void * D.1376;
  void * * D.1375;
  struct 
  {
    struct java.lang.Class * class;
    void * methods[2];
  } * D.1374;
  void * _ref_2_4.3;
  void java.io.PrintStream::<T3d2> (struct java.io.PrintStream *, struct  *) * D.1372;
  void * D.1371;
  void * * D.1370;
  struct 
  {
    struct java.lang.Class * class;
    void * methods[2];
  } * D.1369;
  void * _ref_2_4.2;
  void java.util.concurrent.Semaphore::<T1c3> (struct java.util.concurrent.Semaphore *) * D.1364;
  void * D.1363;
  void * * D.1362;
  struct 
  {
    struct java.lang.Class * class;
    void * methods[2];
  } * D.1361;
  void * _ref_2_4.1;

  D.910 = 0;
  #slot#2#0 = 0;
  #slot#1#1 = #slot#2#0;
  goto *.LJpc=1030;
  *.LJpc=1005:
  D.426 = D.413;
  #ref#2#4 = D.426;
  D.1385 = MEM[(struct MyThread *)#ref#2#4].s2;
  D.430 = D.1385;
  #ref#2#4 = D.430;
  _ref_2_4.1 = #ref#2#4;
  D.1386 = MEM[(struct java.lang.Object *)_ref_2_4.1].vtable;
  D.1361 = D.1386;
  D.1362 = D.1361 + 64;
  D.1387 = *D.1362;
  D.1363 = D.1387;
  D.1364 = (void java.util.concurrent.Semaphore::<T1c3> (struct java.util.concurrent.Semaphore *) *) D.1363;
  D.1364 (_ref_2_4.1);
  if (D.910 == 0) goto <D.1365>; else goto <D.1366>;
  <D.1365>:
  _Jv_InitClass (&java.lang.System.class$$);
  goto <D.1367>;
  <D.1366>:
  <D.1367>:
  D.910 = 1;
  D.912 = out;
  #ref#2#4 = D.912;
  #ref#3#9 = _CD_MyThread[1];
  _ref_2_4.2 = #ref#2#4;
  D.1388 = MEM[(struct java.lang.Object *)_ref_2_4.2].vtable;
  D.1369 = D.1388;
  D.1370 = D.1369 + 248;
  D.1389 = *D.1370;
  D.1371 = D.1389;
  D.1372 = (void java.io.PrintStream::<T3d2> (struct java.io.PrintStream *, struct  *) *) D.1371;
  D.1372 (_ref_2_4.2, #ref#3#9);
  D.1020 = D.413;
  #ref#2#4 = D.1020;
  D.1390 = MEM[(struct MyThread *)#ref#2#4].s1;
  D.1021 = D.1390;
  #ref#2#4 = D.1021;
  _ref_2_4.3 = #ref#2#4;
  D.1391 = MEM[(struct java.lang.Object *)_ref_2_4.3].vtable;
  D.1374 = D.1391;
  D.1375 = D.1374 + 96;
  D.1392 = *D.1375;
  D.1376 = D.1392;
  D.1377 = (void java.util.concurrent.Semaphore::<T1c8> (struct java.util.concurrent.Semaphore *) *) D.1376;
  D.1377 (_ref_2_4.3);
  #slot#1#1 = #slot#1#1 + 1;
  *.LJpc=1030:
  D.1022 = #slot#1#1;
  #slot#2#0 = D.1022;
  #slot#3#10 = 10;
  if (#slot#2#0 < #slot#3#10) goto *.LJpc=1005; else goto <D.1378>;
  <D.1378>:
  goto *.LJpc=1044;
  *.LJpc=1039:
  D.1395 = MEM[(struct java.lang.Throwable * *)#exc_obj + -8B];
  #ref#2#4 = D.1395;
  #ref#1#13 = #ref#2#4;
  D.1070 = #ref#1#13;
  #ref#2#4 = D.1070;
  _ref_2_4.4 = #ref#2#4;
  D.1396 = MEM[(struct java.lang.Object *)_ref_2_4.4].vtable;
  D.1380 = D.1396;
  D.1381 = D.1380 + 96;
  D.1397 = *D.1381;
  D.1382 = D.1397;
  D.1383 = (void java.lang.Throwable::<T421> (struct java.lang.Throwable *) *) D.1382;
  D.1383 (_ref_2_4.4);
  *.LJpc=1044:
  goto <D.1384>;
  <D.1384>:
  return;
  <D.1394>:
  eh_dispatch 1
  resx 1
  <D.1393>:
  #exc_obj = __builtin_eh_pointer (1);
  goto *.LJpc=1039;
}



;; Function helloTwoThreads.<clinit>() (_ZN15helloTwoThreads18__U3c_clinit__U3e_EJvv, funcdef_no=2, decl_uid=1256, cgraph_uid=4, symbol_order=21)

helloTwoThreads.<clinit>() ()
{
  void * D.1403;
  void * D.1402;
  int #slot#2#4;
  void * #ref#1#3;
  void * #ref#0#1;
  void * _ref_1_3.6;
  void * _ref_1_3.5;

  D.1402 = _Jv_AllocObjectNoFinalizer (&java.util.concurrent.Semaphore.class$$);
  #ref#0#1 = D.1402;
  #ref#1#3 = #ref#0#1;
  #ref#0#1 = #ref#1#3;
  #slot#2#4 = 1;
  _ref_1_3.5 = #ref#1#3;
   (_ref_1_3.5, #slot#2#4);
  s1 = #ref#0#1;
  D.1403 = _Jv_AllocObjectNoFinalizer (&java.util.concurrent.Semaphore.class$$);
  #ref#0#1 = D.1403;
  #ref#1#3 = #ref#0#1;
  #ref#0#1 = #ref#1#3;
  #slot#2#4 = 0;
  _ref_1_3.6 = #ref#1#3;
   (_ref_1_3.6, #slot#2#4);
  s2 = #ref#0#1;
  goto <D.1401>;
  <D.1401>:
  return;
}



;; Function () (_ZN15helloTwoThreadsC1Ev, funcdef_no=3, decl_uid=1257, cgraph_uid=5, symbol_order=22)

() (struct helloTwoThreads * D.1275)
{
  void * #ref#1#2;
  struct java.lang.Object * D.1279;
  void * #ref#0#0;
  void * _ref_1_2.7;

  D.1279 = D.1275;
  #ref#1#2 = D.1279;
  _ref_1_2.7 = #ref#1#2;
   (_ref_1_2.7);
  goto <D.1405>;
  <D.1405>:
  return;
}



;; Function helloTwoThreads.main(java.lang.String[]) (_ZN15helloTwoThreads4mainEJvP6JArrayIPN4java4lang6StringEE, funcdef_no=4, decl_uid=1262, cgraph_uid=6, symbol_order=23)

helloTwoThreads.main(java.lang.String[]) (struct java.lang.String[] * D.1282)
{
  void * D.1441;
  struct 
  {
    struct java.lang.Class * class;
    void * methods[2];
  } * D.1440;
  void * D.1439;
  struct 
  {
    struct java.lang.Class * class;
    void * methods[2];
  } * D.1438;
  void * D.1437;
  struct 
  {
    struct java.lang.Class * class;
    void * methods[2];
  } * D.1436;
  void * D.1435;
  struct 
  {
    struct java.lang.Class * class;
    void * methods[2];
  } * D.1434;
  void * D.1433;
  int #slot#4#13;
  int D.1312;
  struct java.util.concurrent.Semaphore * D.1311;
  struct java.io.PrintStream * D.1307;
  struct java.util.concurrent.Semaphore * D.1304;
  int #slot#2#9;
  int #slot#3#8;
  struct MyThread * D.1300;
  struct java.util.concurrent.Semaphore * D.1299;
  struct MyThread * D.1298;
  struct java.util.concurrent.Semaphore * D.1296;
  struct MyThread * D.1295;
  void * #ref#1#5;
  void * #ref#4#3;
  void * #ref#3#1;
  boolean D.1306;
  void java.util.concurrent.Semaphore::<T1c8> (struct java.util.concurrent.Semaphore *) * D.1430;
  void * D.1429;
  void * * D.1428;
  struct 
  {
    struct java.lang.Class * class;
    void * methods[2];
  } * D.1427;
  void * _ref_3_1.13;
  void java.io.PrintStream::<T3d2> (struct java.io.PrintStream *, struct  *) * D.1425;
  void * D.1424;
  void * * D.1423;
  struct 
  {
    struct java.lang.Class * class;
    void * methods[2];
  } * D.1422;
  void * _ref_3_1.12;
  void java.util.concurrent.Semaphore::<T1c3> (struct java.util.concurrent.Semaphore *) * D.1417;
  void * D.1416;
  void * * D.1415;
  struct 
  {
    struct java.lang.Class * class;
    void * methods[2];
  } * D.1414;
  void * _ref_3_1.11;
  void java.lang.Thread::<T160> (struct java.lang.Thread *) * D.1412;
  void * D.1411;
  void * * D.1410;
  struct 
  {
    struct java.lang.Class * class;
    void * methods[2];
  } * D.1409;
  void * _ref_3_1.10;
  void * _ref_4_3.9;
  const struct java.lang.Class * helloTwoThreads.8;

  D.1306 = 0;
  helloTwoThreads.8 = helloTwoThreads.class$;
  _Jv_InitClass (helloTwoThreads.8);
  D.1433 = _Jv_AllocObjectNoFinalizer (&MyThread.class$$);
  #ref#3#1 = D.1433;
  #ref#4#3 = #ref#3#1;
  #ref#3#1 = #ref#4#3;
  _ref_4_3.9 = #ref#4#3;
   (_ref_4_3.9);
  #ref#1#5 = #ref#3#1;
  D.1295 = #ref#1#5;
  #ref#3#1 = D.1295;
  D.1296 = s1;
  #ref#4#3 = D.1296;
  MEM[(struct MyThread *)#ref#3#1].s1 = #ref#4#3;
  D.1298 = #ref#1#5;
  #ref#3#1 = D.1298;
  D.1299 = s2;
  #ref#4#3 = D.1299;
  MEM[(struct MyThread *)#ref#3#1].s2 = #ref#4#3;
  D.1300 = #ref#1#5;
  #ref#3#1 = D.1300;
  _ref_3_1.10 = #ref#3#1;
  D.1434 = MEM[(struct java.lang.Object *)_ref_3_1.10].vtable;
  D.1409 = D.1434;
  D.1410 = D.1409 + 216;
  D.1435 = *D.1410;
  D.1411 = D.1435;
  D.1412 = (void java.lang.Thread::<T160> (struct java.lang.Thread *) *) D.1411;
  D.1412 (_ref_3_1.10);
  #slot#3#8 = 0;
  #slot#2#9 = #slot#3#8;
  goto *.LJpc=4054;
  *.LJpc=4031:
  D.1304 = s1;
  #ref#3#1 = D.1304;
  _ref_3_1.11 = #ref#3#1;
  D.1436 = MEM[(struct java.lang.Object *)_ref_3_1.11].vtable;
  D.1414 = D.1436;
  D.1415 = D.1414 + 64;
  D.1437 = *D.1415;
  D.1416 = D.1437;
  D.1417 = (void java.util.concurrent.Semaphore::<T1c3> (struct java.util.concurrent.Semaphore *) *) D.1416;
  D.1417 (_ref_3_1.11);
  if (D.1306 == 0) goto <D.1418>; else goto <D.1419>;
  <D.1418>:
  _Jv_InitClass (&java.lang.System.class$$);
  goto <D.1420>;
  <D.1419>:
  <D.1420>:
  D.1306 = 1;
  D.1307 = out;
  #ref#3#1 = D.1307;
  #ref#4#3 = _CD_helloTwoThreads[1];
  _ref_3_1.12 = #ref#3#1;
  D.1438 = MEM[(struct java.lang.Object *)_ref_3_1.12].vtable;
  D.1422 = D.1438;
  D.1423 = D.1422 + 248;
  D.1439 = *D.1423;
  D.1424 = D.1439;
  D.1425 = (void java.io.PrintStream::<T3d2> (struct java.io.PrintStream *, struct  *) *) D.1424;
  D.1425 (_ref_3_1.12, #ref#4#3);
  D.1311 = s2;
  #ref#3#1 = D.1311;
  _ref_3_1.13 = #ref#3#1;
  D.1440 = MEM[(struct java.lang.Object *)_ref_3_1.13].vtable;
  D.1427 = D.1440;
  D.1428 = D.1427 + 96;
  D.1441 = *D.1428;
  D.1429 = D.1441;
  D.1430 = (void java.util.concurrent.Semaphore::<T1c8> (struct java.util.concurrent.Semaphore *) *) D.1429;
  D.1430 (_ref_3_1.13);
  #slot#2#9 = #slot#2#9 + 1;
  *.LJpc=4054:
  D.1312 = #slot#2#9;
  #slot#3#8 = D.1312;
  #slot#4#13 = 5;
  if (#slot#3#8 < #slot#4#13) goto *.LJpc=4031; else goto <D.1431>;
  <D.1431>:
  goto <D.1432>;
  <D.1432>:
  return;
}



;; Function _Jv_global_static_constructor() (_Jv_global_static_constructor, funcdef_no=5, decl_uid=1356, cgraph_uid=10, symbol_order=45)

_Jv_global_static_constructor() ()
{
  _Jv_RegisterResource (&_ZGr8_$_dummy);
  return;
}


