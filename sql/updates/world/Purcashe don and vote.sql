CREATE TABLE purchases_donor (
	account_id INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Account Identifier',
	character_name VARCHAR(12) NOT NULL DEFAULT '' COLLATE 'utf8_general_ci',
	character_guid INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier',
	donation_item_id INT(10) UNSIGNED NOT NULL DEFAULT '0',
	donation_item_name VARCHAR(60) NOT NULL DEFAULT '' COLLATE 'utf8_general_ci',
	donation_item_amount INT(10) UNSIGNED NOT NULL DEFAULT '1',
	date TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
)
COMMENT='Write here a comment if this has been refunded or not.'
COLLATE='latin1_swedish_ci'
ENGINE=MyISAM
;
CREATE TABLE purchases_vote (
	account_id INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Account Identifier',
	character_name VARCHAR(12) NOT NULL DEFAULT '' COLLATE 'utf8_general_ci',
	character_guid INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier',
	vote_item_id INT(10) UNSIGNED NOT NULL DEFAULT '0',
	vote_item_name VARCHAR(60) NOT NULL DEFAULT '' COLLATE 'utf8_general_ci',
	vote_item_amount INT(10) UNSIGNED NOT NULL DEFAULT '1',
	date TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
)
COMMENT='Write here a comment if this has been refunded or not.'
COLLATE='latin1_swedish_ci'
ENGINE=MyISAM
;