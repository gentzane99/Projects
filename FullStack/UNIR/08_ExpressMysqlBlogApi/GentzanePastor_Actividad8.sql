-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema Blog
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema Blog
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `Blog` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci ;
USE `Blog` ;

-- -----------------------------------------------------
-- Table `Blog`.`autores`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Blog`.`autores` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `nombre` VARCHAR(100) NOT NULL,
  `email` VARCHAR(150) NOT NULL,
  `imagen` VARCHAR(255) NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `idautores_UNIQUE` (`id` ASC) VISIBLE,
  UNIQUE INDEX `email_UNIQUE` (`email` ASC) VISIBLE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Blog`.`posts`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Blog`.`posts` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `titulo` VARCHAR(150) NOT NULL,
  `descripcion` TEXT NOT NULL,
  `fechaCreacion` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `categoria` VARCHAR(100) NOT NULL,
  `idAutores` INT NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `idposts_UNIQUE` (`id` ASC) VISIBLE,
  INDEX `fk_posts_autores_idx` (`idAutores` ASC) VISIBLE,
  CONSTRAINT `fk_posts_autores`
    FOREIGN KEY (`idAutores`)
    REFERENCES `Blog`.`autores` (`id`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
