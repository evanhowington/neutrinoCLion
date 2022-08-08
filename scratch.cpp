
/*
 * conditional statements relating to while loop
 * */
//            if (ckmL(0, 0) > CKMabsolute(0, 0) || ckmL(0, 1) > CKMabsolute(0, 1) ||
//                ckmL(0, 2) > CKMabsolute(0, 2) || ckmL(1, 0) > CKMabsolute(1, 0) ||
//                ckmL(1, 1) > CKMabsolute(1, 1) || ckmL(1, 2) > CKMabsolute(1, 2) ||
//                ckmL(2, 0) > CKMabsolute(2, 0) || ckmL(2, 1) > CKMabsolute(2, 1) ||
//                ckmL(2, 2) > CKMabsolute(2, 2)) {
//                ++small;
//                std::cout << small << " are too small\n";
//                std::cout << large << " are too large\n";
//                std::cout << good << " are good\n";
//                csv.open("data.csv", std::ios::app);
//                csv << a << "," << kappa << ", small, " << vu1 << "," << vu2 << "," << vu3 << "," << vu4 << "," << vu5
//                    << "," << vu6 << "," << vd1 << "," << vd2 << "," << vd3 << "," << vd4 << "," << vd5 << "," << vd6
//                    << "," << CKMabsolute(0, 0) << "," << CKMabsolute(0, 1) << "," << CKMabsolute(0, 2)
//                    << "," << CKMabsolute(1, 0) << "," << CKMabsolute(1, 1) << "," << CKMabsolute(1, 2)
//                    << "," << CKMabsolute(2, 0) << "," << CKMabsolute(2, 1) << "," << CKMabsolute(2, 2)
//                    << "," << MajoranaVal(0, 0) << "," << MajoranaVal(1, 0) << "," << MajoranaVal(2, 0)
//                    << "," << PMNSabs(0, 0) << "," << PMNSabs(0, 1) << "," << PMNSabs(0, 2) << ","
//                    << PMNSabs(1, 0) << "," << PMNSabs(1, 1) << "," << PMNSabs(1, 2) << ","
//                    << PMNSabs(2, 0) << "," << PMNSabs(2, 1) << "," << PMNSabs(2, 2) << std::endl;
//
//            } else if (CKMabsolute(0, 0) > ckmU(0, 0) || CKMabsolute(0, 1) > ckmU(0, 1) ||
//                       CKMabsolute(0, 2) > ckmU(0, 2) || CKMabsolute(1, 0) > ckmU(1, 0) ||
//                       CKMabsolute(1, 1) > ckmU(1, 1) || CKMabsolute(1, 2) > ckmU(1, 2) ||
//                       CKMabsolute(2, 0) > ckmU(2, 0) || CKMabsolute(2, 1) > ckmU(2, 1) ||
//                       CKMabsolute(2, 2) > ckmU(2, 2)) {
//                ++large;
//                std::cout << small << " are too small\n";
//                std::cout << large << " are too large\n";
//                std::cout << good << " are good\n";
//                csv.open("data.csv", std::ios::app);
//                csv << a << "," << kappa << ", small, " << vu1 << "," << vu2 << "," << vu3 << "," << vu4 << "," << vu5
//                    << "," << vu6 << "," << vd1 << "," << vd2 << "," << vd3 << "," << vd4 << "," << vd5 << "," << vd6
//                    << "," << CKMabsolute(0, 0) << "," << CKMabsolute(0, 1) << "," << CKMabsolute(0, 2)
//                    << "," << CKMabsolute(1, 0) << "," << CKMabsolute(1, 1) << "," << CKMabsolute(1, 2)
//                    << "," << CKMabsolute(2, 0) << "," << CKMabsolute(2, 1) << "," << CKMabsolute(2, 2)
//                    << "," << MajoranaVal(0, 0) << "," << MajoranaVal(1, 0) << "," << MajoranaVal(2, 0)
//                    << "," << PMNSabs(0, 0) << "," << PMNSabs(0, 1) << "," << PMNSabs(0, 2) << ","
//                    << PMNSabs(1, 0) << "," << PMNSabs(1, 1) << "," << PMNSabs(1, 2) << ","
//                    << PMNSabs(2, 0) << "," << PMNSabs(2, 1) << "," << PMNSabs(2, 2) << std::endl;
//            } else {
//                ++good;
//                std::cout << small << " are too small\n";
//                std::cout << large << " are too large\n";
//                std::cout << good << " are good\n";
//                csv.open("data.csv", std::ios::app);
//                csv << a << "," << kappa << ", small, " << vu1 << "," << vu2 << "," << vu3 << "," << vu4 << "," << vu5
//                    << "," << vu6 << "," << vd1 << "," << vd2 << "," << vd3 << "," << vd4 << "," << vd5 << "," << vd6
//                    << "," << CKMabsolute(0, 0) << "," << CKMabsolute(0, 1) << "," << CKMabsolute(0, 2)
//                    << "," << CKMabsolute(1, 0) << "," << CKMabsolute(1, 1) << "," << CKMabsolute(1, 2)
//                    << "," << CKMabsolute(2, 0) << "," << CKMabsolute(2, 1) << "," << CKMabsolute(2, 2)
//                    << "," << MajoranaVal(0, 0) << "," << MajoranaVal(1, 0) << "," << MajoranaVal(2, 0)
//                    << "," << PMNSabs(0, 0) << "," << PMNSabs(0, 1) << "," << PMNSabs(0, 2) << ","
//                    << PMNSabs(1, 0) << "," << PMNSabs(1, 1) << "," << PMNSabs(1, 2) << ","
//                    << PMNSabs(2, 0) << "," << PMNSabs(2, 1) << "," << PMNSabs(2, 2) << std::endl;
//            }

/*
 * threading()
 * */
//double threading(double deltaQ, double deltaL, double tol)
//{
//    std::thread t1(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t2(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t3(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t4(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t5(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t6(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t7(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t8(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t9(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t10(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t11(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t12(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t13(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t14(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t15(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t16(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t17(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t18(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t19(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t20(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t21(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t22(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t23(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t24(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t25(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t26(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t27(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t28(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t29(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t30(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t31(findYukawaMatrices, deltaQ, deltaL, tol);
//    std::thread t32(findYukawaMatrices, deltaQ, deltaL, tol);
//
//    t1.join();
//    t2.join();
//    t3.join();
//    t4.join();
//    t5.join();
//    t6.join();
//    t7.join();
//    t8.join();
//    t9.join();
//    t10.join();
//    t11.join();
//    t12.join();
//    t13.join();
//    t14.join();
//    t15.join();
//    t16.join();
//    t17.join();
//    t18.join();
//    t19.join();
//    t20.join();
//    t21.join();
//    t22.join();
//    t23.join();
//    t24.join();
//    t25.join();
//    t26.join();
//    t27.join();
//    t28.join();
//    t29.join();
//    t30.join();
//    t31.join();
//    t32.join();
//
//    return 0;
//}

/*
 * 1) these are the values for the Higgs VEVs up, down, and Kahler parameter kappa
 * 2) use them to verify results from the paper to ensure the code is working properly
 * before attempting to randomize values
 * */
//        vu1 = 0.0000142;
//        vu2 = 0.00002408185;
//        vu3 = 1.0;
//        vu4 = 0.000000345;
//        vu5 = 0.00404;
//        vu6 = 0.005960855;
//
//        vd1 = 0.0028224;
//        vd2 = 0.045;
//        vd3 = 1.0;
//        vd4 = 0.0010105;
//        vd5 = 0.0266;
//        vd6 = 1.0;
//
//        kappa = 58.7;