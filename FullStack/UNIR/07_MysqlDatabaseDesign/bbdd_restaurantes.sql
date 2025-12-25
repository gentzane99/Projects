SET FOREIGN_KEY_CHECKS=0;

-- -----------------------------------------------------
-- Table `restaurante`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `restaurante` (
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `nombre` VARCHAR(100) NOT NULL,
  `direccion` VARCHAR(200) NOT NULL,
  `telefono` VARCHAR(20) NOT NULL,
  `encargado` VARCHAR(20) NOT NULL,
  `is_open` TINYINT UNSIGNED NOT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mesa`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mesa` (
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `nombre` VARCHAR(10) NOT NULL,
  `max_comensales` TINYINT UNSIGNED NOT NULL,
  `restaurante_id` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_mesa_restaurante_idx` (`restaurante_id` ASC),
  CONSTRAINT `fk_mesa_restaurante`
    FOREIGN KEY (`restaurante_id`)
    REFERENCES `restaurante` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `cliente`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `cliente` (
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `nombre` VARCHAR(100) NOT NULL,
  `telefono` VARCHAR(20) NOT NULL,
  `email` VARCHAR(200) NOT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `favorito`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `favorito` (
  `cliente_id` INT UNSIGNED NOT NULL,
  `restaurante_id` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`cliente_id`, `restaurante_id`),
  INDEX `fk_cliente_has_restaurante_restaurante1_idx` (`restaurante_id` ASC),
  INDEX `fk_cliente_has_restaurante_cliente1_idx` (`cliente_id` ASC),
  CONSTRAINT `fk_cliente_has_restaurante_cliente1`
    FOREIGN KEY (`cliente_id`)
    REFERENCES `cliente` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_cliente_has_restaurante_restaurante1`
    FOREIGN KEY (`restaurante_id`)
    REFERENCES `restaurante` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `reserva`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `reserva` (
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `cliente_id` INT UNSIGNED NOT NULL,
  `mesa_id` INT UNSIGNED NOT NULL,
  `fecha_reserva` DATETIME NOT NULL,
  `comensales` TINYINT NOT NULL,
  INDEX `fk_cliente_has_mesa_mesa1_idx` (`mesa_id` ASC),
  INDEX `fk_cliente_has_mesa_cliente1_idx` (`cliente_id` ASC),
  PRIMARY KEY (`id`),
  CONSTRAINT `fk_cliente_has_mesa_cliente1`
    FOREIGN KEY (`cliente_id`)
    REFERENCES `cliente` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_cliente_has_mesa_mesa1`
    FOREIGN KEY (`mesa_id`)
    REFERENCES `mesa` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

INSERT INTO `restaurante` (`id`, `nombre`, `direccion`, `telefono`, `encargado`, `is_open`) VALUES
(1, 'Restaurante #1', 'Direccion 1', '123456789', 'Encargado A', 1),
(2, 'Restaurante #2', 'Direccion 2', '123456780', 'Encargado B', 0),
(3, 'Restaurante #3', 'Direccion 3', '123456781', 'Encargado C', 1),
(4, 'Restaurante #4', 'Direccion 4', '123456782', 'Encargado D', 0),
(5, 'Restaurante #5', 'Direccion 5', '123456783', 'Encargado E', 1);

INSERT INTO `mesa` (`id`, `nombre`, `max_comensales`, `restaurante_id`) VALUES
(1, 'Mesa #1.1', 4, 1),
(2, 'Mesa #1.2', 4, 1),
(3, 'Mesa #1.3', 4, 1),
(4, 'Mesa #2.1', 4, 2),
(5, 'Mesa #2.2', 4, 2),
(6, 'Mesa #2.3', 4, 2),
(7, 'Mesa #3.1', 3, 3),
(8, 'Mesa #3.2', 4, 3),
(9, 'Mesa #3.3', 4, 3),
(10, 'Mesa #4.1', 4, 4),
(11, 'Mesa #4.2', 4, 4),
(12, 'Mesa #4.3', 4, 4),
(13, 'Mesa #5.1', 1, 5),
(14, 'Mesa #5.2', 2, 5),
(15, 'Mesa #5.3', 4, 5);

INSERT INTO `cliente` (`id`, `nombre`, `telefono`, `email`) VALUES
(1, 'Cliente #1', '123456784', 'cliente1@example.com'),
(2, 'Cliente #2', '123456785', 'cliente2@example.com'),
(3, 'Cliente #3', '123456786', 'cliente3@example.com'),
(4, 'Cliente #4', '123456787', 'cliente4@example.com');

INSERT INTO `favorito` (`cliente_id`, `restaurante_id`) VALUES
(1, 1),
(1, 2),
(1, 3),
(2, 2),
(2, 5),
(3, 1),
(3, 3),
(3, 4),
(4, 2),
(4, 5);

INSERT INTO `reserva` (`id`, `cliente_id`, `mesa_id`, `fecha_reserva`, `comensales`) VALUES
(1, 1, 3, '2024-03-14 19:30:00', 4),
(2, 4, 2, '2024-03-14 19:00:00', 4),
(3, 4, 3, '2024-03-14 18:00:00', 4),
(4, 1, 1, '2024-04-01 18:00:00', 4),
(5, 2, 1, '2024-04-01 19:00:00', 5),
(6, 3, 1, '2024-04-01 20:00:00', 6),
(7, 4, 1, '2024-04-01 21:00:00', 7),
(8, 1, 4, '2024-04-01 18:00:00', 4),
(9, 2, 4, '2024-04-01 19:00:00', 5),
(10, 3, 4, '2025-04-10 17:00:00', 6),
(11, 4, 4, '2024-04-01 21:00:00', 7),
(12, 1, 7, '2024-04-01 18:00:00', 3),
(13, 2, 7, '2024-04-01 19:00:00', 5),
(14, 3, 7, '2024-04-01 20:00:00', 6),
(15, 4, 7, '2024-04-01 21:00:00', 7),
(16, 1, 14, '2024-12-31 19:00:00', 2);

SET FOREIGN_KEY_CHECKS=1;