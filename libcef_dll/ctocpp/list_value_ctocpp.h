// Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//

#ifndef CEF_LIBCEF_DLL_CTOCPP_LIST_VALUE_CTOCPP_H_
#define CEF_LIBCEF_DLL_CTOCPP_LIST_VALUE_CTOCPP_H_
#pragma once

#ifndef USING_CEF_SHARED
#pragma message("Warning: "__FILE__" may be accessed wrapper-side only")
#else  // USING_CEF_SHARED

#include "include/cef_values.h"
#include "include/capi/cef_values_capi.h"
#include "libcef_dll/ctocpp/ctocpp.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class CefListValueCToCpp
    : public CefCToCpp<CefListValueCToCpp, CefListValue, cef_list_value_t> {
 public:
  explicit CefListValueCToCpp(cef_list_value_t* str)
      : CefCToCpp<CefListValueCToCpp, CefListValue, cef_list_value_t>(str) {}
  virtual ~CefListValueCToCpp() {}

  // CefListValue methods
  virtual bool IsValid() OVERRIDE;
  virtual bool IsOwned() OVERRIDE;
  virtual bool IsReadOnly() OVERRIDE;
  virtual CefRefPtr<CefListValue> Copy() OVERRIDE;
  virtual bool SetSize(size_t size) OVERRIDE;
  virtual size_t GetSize() OVERRIDE;
  virtual bool Clear() OVERRIDE;
  virtual bool Remove(int index) OVERRIDE;
  virtual CefValueType GetType(int index) OVERRIDE;
  virtual bool GetBool(int index) OVERRIDE;
  virtual int GetInt(int index) OVERRIDE;
  virtual double GetDouble(int index) OVERRIDE;
  virtual CefString GetString(int index) OVERRIDE;
  virtual CefRefPtr<CefBinaryValue> GetBinary(int index) OVERRIDE;
  virtual CefRefPtr<CefDictionaryValue> GetDictionary(int index) OVERRIDE;
  virtual CefRefPtr<CefListValue> GetList(int index) OVERRIDE;
  virtual bool SetNull(int index) OVERRIDE;
  virtual bool SetBool(int index, bool value) OVERRIDE;
  virtual bool SetInt(int index, int value) OVERRIDE;
  virtual bool SetDouble(int index, double value) OVERRIDE;
  virtual bool SetString(int index, const CefString& value) OVERRIDE;
  virtual bool SetBinary(int index, CefRefPtr<CefBinaryValue> value) OVERRIDE;
  virtual bool SetDictionary(int index,
      CefRefPtr<CefDictionaryValue> value) OVERRIDE;
  virtual bool SetList(int index, CefRefPtr<CefListValue> value) OVERRIDE;
};

#endif  // USING_CEF_SHARED
#endif  // CEF_LIBCEF_DLL_CTOCPP_LIST_VALUE_CTOCPP_H_

