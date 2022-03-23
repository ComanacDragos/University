x_vals = [1, 2];
f_vals = [0, 0.6931];
df_vals = [1, 0.5];

actual_val = log(1.5)
pred_val = hermite(1.5, x_vals, f_vals, df_vals)

error = abs(actual_val - pred_val)