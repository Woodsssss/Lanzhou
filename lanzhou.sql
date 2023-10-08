/*
 Navicat Premium Data Transfer

 Source Server         : Lanzhou1
 Source Server Type    : MySQL
 Source Server Version : 80034
 Source Host           : localhost:3306
 Source Schema         : lanzhou

 Target Server Type    : MySQL
 Target Server Version : 80034
 File Encoding         : 65001

 Date: 07/10/2023 15:31:03
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for checkrelation
-- ----------------------------
DROP TABLE IF EXISTS `checkrelation`;
CREATE TABLE `checkrelation`  (
  `Id` int(0) NOT NULL COMMENT '连接表编号',
  `FatherId` int(0) NOT NULL COMMENT '父检测项编号',
  `ChildId` int(0) NOT NULL COMMENT '子检测项编号',
  PRIMARY KEY (`Id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of checkrelation
-- ----------------------------
INSERT INTO `checkrelation` VALUES (1, 1, 1);

-- ----------------------------
-- Table structure for childcheck
-- ----------------------------
DROP TABLE IF EXISTS `childcheck`;
CREATE TABLE `childcheck`  (
  `Id` int(0) NOT NULL COMMENT '子检测项编号',
  `Name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '子检测项名称',
  PRIMARY KEY (`Id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of childcheck
-- ----------------------------
INSERT INTO `childcheck` VALUES (1, '火警1');
INSERT INTO `childcheck` VALUES (2, '火警2');

-- ----------------------------
-- Table structure for parentcheck
-- ----------------------------
DROP TABLE IF EXISTS `parentcheck`;
CREATE TABLE `parentcheck`  (
  `Id` int(0) NOT NULL COMMENT '父检测项编号',
  `Name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '父检测项名称',
  PRIMARY KEY (`Id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of parentcheck
-- ----------------------------
INSERT INTO `parentcheck` VALUES (1, '基准电压测试');
INSERT INTO `parentcheck` VALUES (2, '信号测试');

-- ----------------------------
-- Table structure for testproject
-- ----------------------------
DROP TABLE IF EXISTS `testproject`;
CREATE TABLE `testproject`  (
  `Id` int(0) NOT NULL COMMENT '测试工程编号',
  `ProjectName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '测试工程名称',
  `TesterId` int(0) NOT NULL COMMENT '测试人员编号',
  `EquipmentModel` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '测试设备型号',
  `Time` datetime(0) NOT NULL COMMENT '测试时间',
  `State` int(0) NOT NULL COMMENT '测试状态（0为未测试、1为已测试、2为进行中）',
  `UpcomingTests` int(0) NOT NULL COMMENT '若状态为进行中，即记录将进行的测试序号',
  `StepsId` int(0) NOT NULL COMMENT '测试步骤',
  `ResultId` int(0) NOT NULL COMMENT '测试结果id',
  PRIMARY KEY (`Id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of testproject
-- ----------------------------
INSERT INTO `testproject` VALUES (1, '测试工程1', 1, 'GJX-7', '2023-10-03 15:09:55', 0, 1, 1, 1);

-- ----------------------------
-- Table structure for testresult
-- ----------------------------
DROP TABLE IF EXISTS `testresult`;
CREATE TABLE `testresult`  (
  `Id` int(0) NOT NULL COMMENT '测试结果编号',
  `Result` text CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '具体测试结果',
  PRIMARY KEY (`Id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of testresult
-- ----------------------------
INSERT INTO `testresult` VALUES (1, '检测通过');
INSERT INTO `testresult` VALUES (2, '检测未通过');

-- ----------------------------
-- Table structure for teststep
-- ----------------------------
DROP TABLE IF EXISTS `teststep`;
CREATE TABLE `teststep`  (
  `Id` int(0) NOT NULL COMMENT '测试步骤编号',
  `Name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '测试步骤名称',
  `CreatedById` int(0) NOT NULL COMMENT '创建人员编号',
  `TestMode` int(0) NOT NULL COMMENT '测试模式(0为手动测试，1为自动测试)',
  `Steps` text CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '测试详细步骤',
  PRIMARY KEY (`Id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of teststep
-- ----------------------------
INSERT INTO `teststep` VALUES (1, '全自动测试', 1, 1, '1,2,3,4');
INSERT INTO `teststep` VALUES (2, '电压测试', 1, 2, '1,2,3,4');

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `Id` int(0) NOT NULL COMMENT '用户编号',
  `Name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '用户名称',
  `Permission` int(0) NOT NULL COMMENT '用户权限(0为管理员，1为普通用户)',
  `Password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '用户密码',
  PRIMARY KEY (`Id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES (1, 'xulin', 0, '123456');
INSERT INTO `user` VALUES (2, 'zhangxu', 1, '123456');

SET FOREIGN_KEY_CHECKS = 1;
