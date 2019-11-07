-- phpMyAdmin SQL Dump
-- version 4.8.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: May 03, 2018 at 01:39 PM
-- Server version: 10.1.31-MariaDB
-- PHP Version: 7.2.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `itsatis`
--

-- --------------------------------------------------------

--
-- Table structure for table `density`
--

CREATE TABLE `density` (
  `DensityId` int(11) NOT NULL,
  `Timestamp` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `LaneId` int(11) NOT NULL,
  `Density` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Table structure for table `junction`
--

CREATE TABLE `junction` (
  `JunctionId` int(11) NOT NULL,
  `NoofLanes` int(11) NOT NULL,
  `NameofJunction` varchar(50) NOT NULL,
  `A` varchar(30) NOT NULL,
  `B` varchar(30) NOT NULL,
  `C` varchar(30) NOT NULL,
  `D` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `junction`
--

INSERT INTO `junction` (`JunctionId`, `NoofLanes`, `NameofJunction`, `A`, `B`, `C`, `D`) VALUES
(1, 5, 'Turner Rd Junction', '19.059465,72.836911', '19.059579,72.836929', '19.059576,72.836767', '19.059465,72.836768'),
(2, 3, 'RD National College Junction', '19.06359,72.83521', '19.06357,72.83512', '19.06372,72.83515', '19.06369,72.83503'),
(3, 4, 'Dena Bank Kandivali Station We', '19.20386,72.84951', '19.20386,72.84963', '19.20434,72.84963', '19.20433,72.84974'),
(4, 4, 'Patel Nagar Junction', '19.20550,72.84363', '19.20566,72.84365', '19.20566,72.84357', '19.20551,72.84353');

-- --------------------------------------------------------

--
-- Table structure for table `lane`
--

CREATE TABLE `lane` (
  `LaneId` int(2) NOT NULL,
  `JunctionId` int(2) NOT NULL,
  `StartLat` float(10,6) DEFAULT NULL,
  `StartLng` float(10,6) NOT NULL,
  `EndLat` float(10,6) DEFAULT NULL,
  `EndLng` float(10,6) DEFAULT NULL,
  `PolylinePoints` varchar(200) NOT NULL DEFAULT '',
  `Lane` varchar(2) NOT NULL,
  `NoofSensors` int(2) NOT NULL,
  `Direction` varchar(2) NOT NULL,
  `CurrentTraffic` int(2) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `lane`
--

INSERT INTO `lane` (`LaneId`, `JunctionId`, `StartLat`, `StartLng`, `EndLat`, `EndLng`, `PolylinePoints`, `Lane`, `NoofSensors`, `Direction`, `CurrentTraffic`) VALUES
(1, 1, 19.059210, 72.836746, 19.058640, 72.836678, 'spisB{|p{LXBx@Dv@D\\B', 'A', 5, 'N', 0),
(2, 1, 19.059540, 72.836639, 19.059410, 72.835258, 'gqisBw|p{L@^D|@HhAHjBBj@', 'B', 5, 'E', 1),
(3, 1, 19.059811, 72.836761, 19.061680, 72.835983, 'irisBi}p{LGJMHSHYHg@Pm@Rq@ToDbA]H', 'C', 5, 'S', 2),
(4, 1, 19.059780, 72.837013, 19.060640, 72.837189, 'qqisBw}p{LaA]aCW_BGsAG', 'D', 5, 'S', 3),
(5, 1, 19.059469, 72.836937, 19.059130, 72.837418, 'upisB}}p{L@[FUJORMNIXKb@Qh@Y\\S', 'E', 5, 'W', 4),
(6, 2, 19.063560, 72.835114, 19.063089, 72.835312, 'ijjsBmrp{LJCNGRGJCx@WfA]n@SlA_@', 'A', 5, 'N', 0),
(7, 2, 19.063681, 72.835022, 19.063620, 72.834686, '_kjsB{qp{LFZBd@', 'B', 5, 'E', 1),
(8, 2, 19.063721, 72.835136, 19.064760, 72.834717, 'gkjsBsrp{Lm@Ri@Pg@Nk@N_@JE@', 'C', 5, 'S', 2),
(9, 3, 19.204041, 72.849579, 19.203060, 72.849350, 'kxetB{ls{LZHPB|@Jh@Ht@J', 'A', 5, 'N', 3),
(10, 3, 19.204170, 72.849548, 19.204679, 72.847862, 'ayetB{ls{LGb@Mr@K^Kd@I`@Ov@Qx@Id@', 'B', 5, 'W', 4),
(11, 3, 19.204180, 72.849693, 19.205450, 72.850014, 'cyetBqms{La@Gc@Ia@Gm@I]Ii@G_@I', 'C', 5, 'S', 0),
(12, 3, 19.204081, 72.849701, 19.204081, 72.850082, 'oxetBqms{L?S?[?M?O', 'D', 5, 'E', 1),
(13, 4, 19.205530, 72.843567, 19.204679, 72.843468, 'qaftBigr{LL@R@f@Df@B~@F`@B', 'A', 5, 'N', 2),
(14, 4, 19.205629, 72.843567, 19.205681, 72.841850, 'ebftBigr{LC^Ab@CXCXC|@Af@C`@?ZDb@HZ', 'B', 5, 'E', 3),
(15, 4, 19.205650, 72.843613, 19.206699, 72.843742, 'ibftBsgr{LUCWCg@Gk@IYC]?KBK@', 'C', 5, 'S', 4),
(16, 4, 19.205549, 72.843620, 19.205191, 72.845596, 'uaftBsgr{LDi@Bi@De@Da@Dk@B]Di@DWJi@D]H]', 'D', 5, 'W', 0);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `density`
--
ALTER TABLE `density`
  ADD PRIMARY KEY (`DensityId`),
  ADD KEY `LaneId` (`LaneId`);

--
-- Indexes for table `junction`
--
ALTER TABLE `junction`
  ADD PRIMARY KEY (`JunctionId`);

--
-- Indexes for table `lane`
--
ALTER TABLE `lane`
  ADD PRIMARY KEY (`LaneId`),
  ADD KEY `JunctionId` (`JunctionId`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `density`
--
ALTER TABLE `density`
  MODIFY `DensityId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1;

--
-- AUTO_INCREMENT for table `junction`
--
ALTER TABLE `junction`
  MODIFY `JunctionId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `lane`
--
ALTER TABLE `lane`
  MODIFY `LaneId` int(2) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=17;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `density`
--
ALTER TABLE `density`
  ADD CONSTRAINT `density_ibfk_1` FOREIGN KEY (`LaneId`) REFERENCES `lane` (`LaneId`);

--
-- Constraints for table `lane`
--
ALTER TABLE `lane`
  ADD CONSTRAINT `lane_ibfk_1` FOREIGN KEY (`JunctionId`) REFERENCES `junction` (`JunctionId`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
