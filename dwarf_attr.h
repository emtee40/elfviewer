#ifndef DWARF_ATTR_H
#define DWARF_ATTR_H

typedef enum{
	DW_TAG_array_type = 0x01,
	DW_TAG_class_type,
	DW_TAG_entry_point,
	DW_TAG_enumeration_type,
	DW_TAG_formal_parameter,
	DW_TAG_impored_declaration = 0x08,
	DW_TAG_label = 0x0a,
	DW_TAG_lexical_block,
	DW_TAG_member = 0x0d,
	DW_TAG_pointer_type = 0x0f,
	DW_TAG_reference_type,
	DW_TAG_compile_unit,
	DW_TAG_string_type,
	DW_TAG_structure_type,
	DW_TAG_subroutine_type = 0x15,
	DW_TAG_typedef,
	DW_TAG_union_type,
	DW_TAG_unspecified_parameters,
	DW_TAG_variant,
	DW_TAG_common_block,
	DW_TAG_common_inclusion,
	DW_TAG_inheritance,
	DW_TAG_inlined_subroutine,
	DW_TAG_module,
	DW_TAG_ptr_to_member_type,
	DW_TAG_set_type,
	DW_TAG_subrange_type,
	DW_TAG_with_stmt,
	DW_TAG_access_declaration,
	DW_TAG_base_type,
	DW_TAG_catch_block,
	DW_TAG_constant,
	DW_TAG_enumerator,
	DW_TAG_file_type,
	DW_TAG_friend,
	DW_TAG_namelist,
	DW_TAG_namelist_item,
	DW_TAG_packed_type,
	DW_TAG_subprogram,
	DW_TAG_template_type_parameter,
	DW_TAG_template_value_parameter,
	DW_TAG_thrown_type,
	DW_TAG_try_block,
	DW_TAG_variant_part,
	DW_TAG_variable,
	DW_TAG_volatile_type,
	DW_TAG_dwarf_procedure,
	DW_TAG_restrict_type,
	DW_TAG_interface_type,
	DW_TAG_namespace,
	DW_TAG_imported_module,
	DW_TAG_unspecified_type,
	DW_TAG_partial_unit,
	DW_TAG_condition,
	DW_TAG_shared_type,
	DW_TAG_type_unit,
	DW_TAG_rvalue_reference_type,
	DW_TAG_template_alias,
	DW_TAG_lo_user =0x4080,
	DW_TAG_hi_user = 0xffff
}TAG_NAME;

#define DW_CHILDREN_no	0x00
#define DW_CHILDREN_yes	0x01

typedef enum{
	DW_AT_sibling = 0x01,
	DW_AT_location,
	DW_AT_name,
	DW_AT_ordering = 0x09,
	DW_AT_byte_size = 0x0b,
	DW_AT_bit_offset,
	DW_AT_bit_size,
	DW_AT_stmt_list = 0x10,
	DW_AT_low_pc,
	DW_AT_high_pc,
	DW_AT_language,
	DW_AT_discr	= 0x15,
	DW_AT_discr_value,
	DW_AT_visibility,
	DW_AT_import,
	DW_AT_string_length,
	DW_AT_common_reference = 0x1a,
	DW_AT_comp_dir,
	DW_AT_const_value,
	DW_AT_containing_type,
	DW_AT_default_value,
	DW_AT_inline = 0x20,
	DW_AT_is_optional,
	DW_AT_lower_bound,
	DW_AT_producer = 0x25,
	DW_AT_prototyped = 0x27,
	DW_AT_return_addr = 0x2a,
	DW_AT_start_scope = 0x2c,
	DW_AT_bit_stride = 0x2e,
	DW_AT_upper_bound = 0x2f,
	DW_AT_abstract_origin = 0x31,
	DW_AT_accessibility,
	DW_AT_address_class,
	DW_AT_artificial,
	DW_AT_base_types,
	DW_AT_calling_convention,
	DW_AT_count,
	DW_AT_data_member_location,
	DW_AT_decl_column,
	DW_AT_decl_file,
	DW_AT_decl_line,
	DW_AT_declaration,
	DW_AT_discr_list,
	DW_AT_encoding,
	DW_AT_external,
	DW_AT_frame_base,
	DW_AT_friend,
	DW_AT_identifier_case,
	DW_AT_macro_info,
	DW_AT_namelist_item,
	DW_AT_priority,
	DW_AT_segment,
	DW_AT_specification,
	DW_AT_static_link,
	DW_AT_type,
	DW_AT_use_location,
	DW_AT_variable_parameter,
	DW_AT_virtuality,
	DW_AT_vtable_elem_location,
	DW_AT_allocated,
	DW_AT_associated,
	DW_AT_data_location,
	DW_AT_byte_stride,
	DW_AT_entry_pc,
	DW_AT_use_UTF8,
	DW_AT_extension,
	DW_AT_ranges,
	DW_AT_trampoline,
	DW_AT_call_column,
	DW_AT_call_file,
	DW_AT_call_line,
	DW_AT_description,
	DW_AT_binary_scale,
	DW_AT_decimal_scale,
	DW_AT_small,
	DW_AT_decimal_sign,
	DW_AT_digit_count,
	DW_AT_picture_string,
	DW_AT_mutable,
	DW_AT_threads_scaled,
	DW_AT_explicit,
	DW_AT_object_pointer,
	DW_AT_endianity,
	DW_AT_elemental,
	DW_AT_pure,
	DW_AT_recursive,
	DW_AT_signaure,
	DW_AT_main_subprogram,
	DW_AT_data_bit_offset,		//0x6b	constant.
	DW_AT_const_expr,			//0x6c	flag.
	DW_AT_enum_class,			//0x6d	flag.
	DW_AT_linkage_name,			//0x6e	string.
	DW_AT_lo_user = 0x2000,
	DW_AT_hi_user = 0x3fff
}ATTRIBUTE_NAME;

typedef enum{
	DW_FORM_addr = 0x01,
	DW_FORM_block2 = 0x03,
	DW_FORM_block4,
	DW_FORM_data2,
	DW_FORM_data4,
	DW_FORM_data8,
	DW_FORM_string,
	DW_FORM_block,
	DW_FORM_block1,
	DW_FORM_data1,
	DW_FORM_flag,
	DW_FORM_sdata,
	DW_FORM_strp,
	DW_FORM_udata,
	DW_FORM_ref_addr,
	DW_FORM_ref1,
	DW_FORM_ref2,
	DW_FORM_ref4,
	DW_FORM_ref8,
	DW_FORM_ref_udata,
	DW_FORM_indirect,
	DW_FORM_sec_offset,
	DW_FORM_exprloc,
	DW_FORM_flag_present,
	DW_FORM_ref_sig8,
}ATTRIBUTE_FORM;
#endif	//DWARF_ATTR_H
