/*
 Navicat Premium Data Transfer

 Source Server         : mysql
 Source Server Type    : MySQL
 Source Server Version : 50736
 Source Host           : localhost:3306
 Source Schema         : lanzhou

 Target Server Type    : MySQL
 Target Server Version : 50736
 File Encoding         : 65001

 Date: 01/11/2023 17:10:41
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for step
-- ----------------------------
DROP TABLE IF EXISTS `step`;
CREATE TABLE `step`  (
  `Id` int(11) NOT NULL AUTO_INCREMENT COMMENT '检测项编号',
  `Name` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '检测项名称',
  `Type` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '检测项类型',
  PRIMARY KEY (`Id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 95 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of step
-- ----------------------------
INSERT INTO `step` VALUES (1, '18V测试', '功耗检查');
INSERT INTO `step` VALUES (2, '32V测试', '功耗检查');
INSERT INTO `step` VALUES (3, '18V测试', '基准电压精度检查');
INSERT INTO `step` VALUES (4, '28V测试', '基准电压精度检查');
INSERT INTO `step` VALUES (5, '32V测试', '基准电压精度检查');
INSERT INTO `step` VALUES (6, '火警 1', '输入信号特征检查');
INSERT INTO `step` VALUES (7, '火警 2', '输入信号特征检查');
INSERT INTO `step` VALUES (8, '火警 3', '输入信号特征检查');
INSERT INTO `step` VALUES (9, '火警 4', '输入信号特征检查');
INSERT INTO `step` VALUES (10, '火警 5', '输入信号特征检查');
INSERT INTO `step` VALUES (11, '火警 6', '输入信号特征检查');
INSERT INTO `step` VALUES (12, '火警 7', '输入信号特征检查');
INSERT INTO `step` VALUES (13, '火警 8', '输入信号特征检查');
INSERT INTO `step` VALUES (14, '火警 9', '输入信号特征检查');
INSERT INTO `step` VALUES (15, '火警 10', '输入信号特征检查');
INSERT INTO `step` VALUES (16, '火警 11', '输入信号特征检查');
INSERT INTO `step` VALUES (17, '火警 12', '输入信号特征检查');
INSERT INTO `step` VALUES (18, '临界攻角', '输入信号特征检查');
INSERT INTO `step` VALUES (19, '结冰', '输入信号特征检查');
INSERT INTO `step` VALUES (20, '引气漏', '输入信号特征检查');
INSERT INTO `step` VALUES (21, '剩油 15（1）', '输入信号特征检查');
INSERT INTO `step` VALUES (22, '剩油 15（2）', '输入信号特征检查');
INSERT INTO `step` VALUES (23, '剩油 15（3）', '输入信号特征检查');
INSERT INTO `step` VALUES (24, '剩油 15（4）', '输入信号特征检查');
INSERT INTO `step` VALUES (25, '发动机（1）', '输入信号特征检查');
INSERT INTO `step` VALUES (26, '发动机（2）', '输入信号特征检查');
INSERT INTO `step` VALUES (27, '发动机（3）', '输入信号特征检查');
INSERT INTO `step` VALUES (28, '发动机（4）', '输入信号特征检查');
INSERT INTO `step` VALUES (29, '电源', '输入信号特征检查');
INSERT INTO `step` VALUES (30, '方向舵偏限', '输入信号特征检查');
INSERT INTO `step` VALUES (31, '舵锁定', '输入信号特征检查');
INSERT INTO `step` VALUES (32, '襟翼控制', '输入信号特征检查');
INSERT INTO `step` VALUES (33, '配平', '输入信号特征检查');
INSERT INTO `step` VALUES (34, '液压 1', '输入信号特征检查');
INSERT INTO `step` VALUES (35, '液压 2', '输入信号特征检查');
INSERT INTO `step` VALUES (36, '液压 3', '输入信号特征检查');
INSERT INTO `step` VALUES (37, '超速', '输入信号特征检查');
INSERT INTO `step` VALUES (38, '除冰控制器', '输入信号特征检查');
INSERT INTO `step` VALUES (39, '气囊压力低', '输入信号特征检查');
INSERT INTO `step` VALUES (40, '引气超压 1', '输入信号特征检查');
INSERT INTO `step` VALUES (41, '引气超压 2', '输入信号特征检查');
INSERT INTO `step` VALUES (42, '引气超压 3', '输入信号特征检查');
INSERT INTO `step` VALUES (43, '引气超压 4', '输入信号特征检查');
INSERT INTO `step` VALUES (44, '用氧', '输入信号特征检查');
INSERT INTO `step` VALUES (45, '剩油 45（1）', '输入信号特征检查');
INSERT INTO `step` VALUES (46, '剩油 45（2）', '输入信号特征检查');
INSERT INTO `step` VALUES (47, '剩油 45（3）', '输入信号特征检查');
INSERT INTO `step` VALUES (48, '剩油 45（4）', '输入信号特征检查');
INSERT INTO `step` VALUES (49, '收起落架', '输入信号特征检查');
INSERT INTO `step` VALUES (50, '前应急门', '输入信号特征检查');
INSERT INTO `step` VALUES (51, '后登机门', '输入信号特征检查');
INSERT INTO `step` VALUES (52, '座舱超压', '输入信号特征检查');
INSERT INTO `step` VALUES (53, '自动驾驶仪故\r\n障', '输入信号特征检查');
INSERT INTO `step` VALUES (54, '自动驾驶仪电\r\n源', '输入信号特征检查');
INSERT INTO `step` VALUES (55, '自动油门告警', '输入信号特征检查');
INSERT INTO `step` VALUES (56, '自动油门电源', '输入信号特征检查');
INSERT INTO `step` VALUES (57, '自动拉起', '输入信号特征检查');
INSERT INTO `step` VALUES (58, '自动驾驶仪断\r\n开', '输入信号特征检查');
INSERT INTO `step` VALUES (59, '自动驾驶仪电\r\n源接通', '输入信号特征检查');
INSERT INTO `step` VALUES (60, '自动油门断开', '输入信号特征检查');
INSERT INTO `step` VALUES (61, '自动油门电源\r\n接通', '输入信号特征检查');
INSERT INTO `step` VALUES (62, '真空速', '输入信号特征检查');
INSERT INTO `step` VALUES (63, '电瓶 1', '输入信号特征检查');
INSERT INTO `step` VALUES (64, '电瓶 2', '输入信号特征检查');
INSERT INTO `step` VALUES (65, '电瓶 3', '输入信号特征检查');
INSERT INTO `step` VALUES (66, '电瓶 4', '输入信号特征检查');
INSERT INTO `step` VALUES (67, '起动故障', '输入信号特征检查');
INSERT INTO `step` VALUES (68, '螺桨 1', '输入信号特征检查');
INSERT INTO `step` VALUES (69, '螺桨 2', '输入信号特征检查');
INSERT INTO `step` VALUES (70, '螺桨 3', '输入信号特征检查');
INSERT INTO `step` VALUES (71, '螺桨 4', '输入信号特征检查');
INSERT INTO `step` VALUES (72, '主控液压未通', '输入信号特征检查');
INSERT INTO `step` VALUES (73, '融冰 1', '输入信号特征检查');
INSERT INTO `step` VALUES (74, '融冰 2', '输入信号特征检查');
INSERT INTO `step` VALUES (75, '登机门', '输入信号特征检查');
INSERT INTO `step` VALUES (76, '52 框门', '输入信号特征检查');
INSERT INTO `step` VALUES (77, '左武器舱门', '输入信号特征检查');
INSERT INTO `step` VALUES (78, '右武器舱门', '输入信号特征检查');
INSERT INTO `step` VALUES (79, '浮标活门 A', '输入信号特征检查');
INSERT INTO `step` VALUES (80, '浮标活门 B', '输入信号特征检查');
INSERT INTO `step` VALUES (81, '浮标活门 C', '输入信号特征检查');
INSERT INTO `step` VALUES (82, '浮标活门 D', '输入信号特征检查');
INSERT INTO `step` VALUES (83, '左控液压未通', '输入信号特征检查');
INSERT INTO `step` VALUES (84, '右控液压未通', '输入信号特征检查');
INSERT INTO `step` VALUES (85, '不同级别', '优先级别检查');
INSERT INTO `step` VALUES (86, '相同级别1', '优先级别检查');
INSERT INTO `step` VALUES (87, '相同级别2', '优先级别检查');
INSERT INTO `step` VALUES (88, '相同级别3', '优先级别检查');
INSERT INTO `step` VALUES (89, '余度1', '余度检查');
INSERT INTO `step` VALUES (90, '余度2', '余度检查');
INSERT INTO `step` VALUES (91, '余度3', '余度检查');
INSERT INTO `step` VALUES (92, '余度4', '余度检查');
INSERT INTO `step` VALUES (93, '429检测', '429通信检查');

-- ----------------------------
-- Table structure for testproject
-- ----------------------------
DROP TABLE IF EXISTS `testproject`;
CREATE TABLE `testproject`  (
  `Id` int(11) NOT NULL COMMENT '测试工程编号',
  `ProjectName` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '测试工程名称',
  `TesterId` int(11) NOT NULL COMMENT '测试人员编号',
  `EquipmentModel` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '测试设备型号',
  `Time` datetime(0) NOT NULL COMMENT '测试时间',
  `State` int(11) NOT NULL COMMENT '测试状态（0为未测试、1为已测试、2为进行中）',
  `UpcomingTests` int(11) NOT NULL COMMENT '若状态为进行中，即记录将进行的测试序号',
  `StepsId` int(11) NOT NULL COMMENT '测试步骤',
  `ResultId` int(11) NOT NULL COMMENT '测试结果id',
  PRIMARY KEY (`Id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of testproject
-- ----------------------------
INSERT INTO `testproject` VALUES (1, '测试工程1', 1, 'GJX-7', '2023-10-03 15:09:55', 0, 1, 1, 1);
INSERT INTO `testproject` VALUES (2, '测试工程1', 2, 'GJX-14', '2023-10-07 15:19:09', 0, 2, 2, 2);

-- ----------------------------
-- Table structure for testresult
-- ----------------------------
DROP TABLE IF EXISTS `testresult`;
CREATE TABLE `testresult`  (
  `Id` int(11) NOT NULL COMMENT '测试结果编号',
  `Result` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '具体测试结果',
  PRIMARY KEY (`Id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

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
  `Id` int(11) NOT NULL COMMENT '测试步骤编号',
  `Name` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '测试步骤名称',
  `CreatedById` int(11) NOT NULL COMMENT '创建人员编号',
  `TestMode` int(11) NOT NULL COMMENT '测试模式(0为手动测试，1为自动测试)',
  `Steps` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '测试详细步骤',
  PRIMARY KEY (`Id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of teststep
-- ----------------------------
INSERT INTO `teststep` VALUES (1, '全自动测试', 1, 1, '1');
INSERT INTO `teststep` VALUES (2, '电压测试', 1, 2, '1');

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `Id` int(11) NOT NULL COMMENT '用户编号',
  `Name` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '用户名称',
  `Permission` int(11) NOT NULL COMMENT '用户权限(0为管理员，1为普通用户)',
  `Password` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '用户密码',
  PRIMARY KEY (`Id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES (1, 'xulin', 0, '123456');
INSERT INTO `user` VALUES (2, 'zhangxu', 1, '123456');

SET FOREIGN_KEY_CHECKS = 1;
